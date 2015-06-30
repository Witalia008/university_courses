using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections.ObjectModel;
using Newtonsoft.Json;

namespace UZTracerBGTask.src.Data
{
    public sealed class AppDataManager
    {
        private static string TicketsKey = "ticketsData";
        private static string RequestsKey = "requestsData";

        public static void SaveTickets(IEnumerable<Ticket> tickets)
        {
            Windows.Storage.ApplicationDataContainer roamingSettings =
                Windows.Storage.ApplicationData.Current.RoamingSettings;
            roamingSettings.Values[TicketsKey] = JsonConvert.SerializeObject(tickets);
        }

        public static IEnumerable<Ticket> RetrieveTickets()
        {
            Windows.Storage.ApplicationDataContainer roamingSettings =
                        Windows.Storage.ApplicationData.Current.RoamingSettings;
            if (roamingSettings.Values.ContainsKey(TicketsKey))
            {
                return JsonConvert.DeserializeObject<IEnumerable<Ticket>>(
                    roamingSettings.Values[TicketsKey].ToString());
            }
            return null;
        }

        public static void SaveRequests(IEnumerable<Request> requests)
        {
            Windows.Storage.ApplicationDataContainer roamingSettings =
                Windows.Storage.ApplicationData.Current.RoamingSettings;
            roamingSettings.Values[RequestsKey] = JsonConvert.SerializeObject(requests);
        }

        public static IEnumerable<Request> RetrieveRequests()
        {
            Windows.Storage.ApplicationDataContainer roamingSettings =
                        Windows.Storage.ApplicationData.Current.RoamingSettings;
            if (roamingSettings.Values.ContainsKey(RequestsKey))
            {
                return JsonConvert.DeserializeObject<IEnumerable<Request>>(
                    roamingSettings.Values[RequestsKey].ToString());
            }
            return null;
        }
    }
}
