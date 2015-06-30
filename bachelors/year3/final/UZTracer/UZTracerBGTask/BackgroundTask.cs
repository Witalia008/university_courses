using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.ApplicationModel.Background;
using Windows.Foundation;
using UZTracerBGTask.src;
using UZTracerBGTask.src.Data;
using UZTracerBGTask.src.Net;
using UZTracerBGTask.src.ents;
using Newtonsoft.Json;

namespace UZTracerBGTask
{
    public sealed class BackgroundTask : IBackgroundTask
    {
        public async void Run(IBackgroundTaskInstance taskInstance)
        {
            BackgroundTaskDeferral _deferral = taskInstance.GetDeferral();

            checkTickets();
            await checkRequestsAsyncHelper();

            _deferral.Complete();
        }

        private static void checkTickets()
        {
            IEnumerable<Ticket> tickets = AppDataManager.RetrieveTickets();
            foreach (Ticket tic in tickets)
            {
                if (tic.notifyBeforeDeparture && (tic.departure.GetDateTime() - DateTimeOffset.Now).Hours < 5)
                {
                    tic.notifyBeforeDeparture = false;
                    Notification.SendToast(
                        "У вас потяг " + tic.departure.date.ToString("d"),
                        tic.from + " - " + tic.to + " о " + tic.departure.time,
                        DateTimeOffset.Now.AddSeconds(15),
                        "UZTracer.TicketPage?info&" + JsonConvert.SerializeObject(tic));
                }
            }
            AppDataManager.SaveTickets(tickets);
        }

        private static async Task checkRequestsAsyncHelper()
        {
            IEnumerable<Request> requests = AppDataManager.RetrieveRequests();
            int addedForRequests = 0;
            try
            {
                foreach (Request req in requests)
                {
                    bool found = false;
                    TrainRequest trainReq = new TrainRequest()
                    {
                        from = req.from,
                        to = req.to,
                        date = req.depDateFrame.since,
                        time = req.depTimeFrame.since,
                        roundTrip = false
                    };
                    TrainResponse trainResp;
                    try
                    {
                        trainResp = Factory.Instance.getTrainResponse(
                                await Requests.makeRequestAsync(Requests.TRAIN_URL, trainReq.getParameters()));
                    }
                    catch (Exception) { continue; }
                    foreach (Train train in trainResp.Trains)
                    {
                        int available = 0;
                        foreach (CoachType type in train.CoachTypes)
                        {
                            try
                            {
                                CoachResponse coachResp = Factory.Instance.getCoachResponse(
                                    await Requests.makeRequestAsync(Requests.COACH_URL, train.getParameters(type, false)));
                                foreach (Coach coach in coachResp.Wrapper.Coaches)
                                {
                                    CarriageResponse carResp = Factory.Instance.getCarriageResponse(
                                        await Requests.makeRequestAsync(Requests.CARRIAGE_URL, train.getParameters(coach)));

                                    available += countAvailavle(req, train, type, coach, carResp.Value.Places);
                                }
                            }
                            catch (Exception) { }
                        }

                        if (!req.available.ContainsKey(train.Number))
                        {
                            req.available[train.Number] = 0;
                        }
                        if (available > req.available[train.Number] + 1)
                        {
                            Notification.SendToast(
                                "З'явилось " + (available - req.available[train.Number]) + " місць",
                                train.Number + " " + req.from.Name + " - " + req.to.Name + ", " + train.From.Date,
                                DateTimeOffset.Now.AddSeconds(15),
                                "UZTracer.TrainPage?" + JsonConvert.SerializeObject(train));

                            found = true;
                        }
                        req.available[train.Number] = available;
                    }
                    addedForRequests += found ? 1 : 0;
                }
            }
            catch (Exception) { }
            finally
            {
                Notification.UpdateBadge(addedForRequests);
                AppDataManager.SaveRequests(requests);
            }
        }

        private static int countAvailavle(
            Request req, Train train, CoachType type, Coach coach, IList<IList<int>> places)
        {
             //TODO: correct time and date checking
            if (// Check if stations are correct
                req.from.StationID != train.From.ID || req.to.StationID != train.Till.ID ||
                // Check departure date frame
                !req.depDateFrame.checkInside(train.From.Date.Date) ||
                // Check departure time frame
                !req.depTimeFrame.checkInside(train.From.Date.TimeOfDay) ||
                // Check arrival time frame
                !req.arrTimeFrame.checkInside(train.Till.Date.TimeOfDay) ||
                // Check Price
                coach.Prices[0] / 100.0 > req.maxPrice ||
                // Check travel time
                (train.Till.Date - train.From.Date) > req.maxTravelTime ||
                // Check coach type TODO: FIX
                false)
            {
                return 0;
            }
            int result = 0;
            foreach (var i in places)
            {
                foreach (int place in i)
                {
                    if (// Check if lower are acceptable
                        (req.seatProps.mayLower || place % 2 == 0) &&
                        // Check if upper are acceptable
                        (req.seatProps.mayUpper || place % 2 == 1) &&
                        // Check if side are acceptable TODO: fix for different types of cars
                        (req.seatProps.maySide || place <= 36) &&
                        // Check if toilet-close are acceptable TODO: fix for diff types of carsS
                        (req.seatProps.mayToilet || Math.Abs(36 - place) > 4))
                    {
                        ++result;
                    }
                }
            }

            return result;
        }
    }
}
