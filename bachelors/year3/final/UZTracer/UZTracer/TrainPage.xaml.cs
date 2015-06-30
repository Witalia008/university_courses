using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using UZTracerBGTask.src.ents;
using UZTracerBGTask.src.Net;
using System.Collections;
using Newtonsoft.Json;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkID=390556

namespace UZTracer
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class TrainPage : Page
    {
        private Train train;
        private CoachType type;
        private Coach coach;

        public TrainPage()
        {
            this.InitializeComponent();
        }

        /// <summary>
        /// Invoked when this page is about to be displayed in a Frame.
        /// </summary>
        /// <param name="e">Event data that describes how this page was reached.
        /// This parameter is typically used to configure the page.</param>
        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            if (e.Parameter.GetType() == typeof(Train))
            {
                train = e.Parameter as Train;
            }
            else
            {
                // Probably more info will be sent
                train = JsonConvert.DeserializeObject<Train>(e.Parameter.ToString());
            }
            infoPanel.DataContext = train;
            dur.Text = (train.Till.Date - train.From.Date).ToString();
            coaches.DataContext = null;
            places.DataContext = null;
        }

        private async void CoachTypes_ItemClick(object sender, ItemClickEventArgs e)
        {
            try
            {
                type = e.ClickedItem as CoachType;
                // TODO: fix roundTrip
                IDictionary<string, string> parameters = train.getParameters(type, false);
                string res = await Requests.makeRequestAsync(Requests.COACH_URL, parameters);
                //debugOutput.Text = res;
                CoachResponse resp = Factory.Instance.getCoachResponse(res);
                coaches.DataContext = resp.Wrapper.Coaches;
                places.DataContext = null;
            }
            catch (Exception ex)
            {
                debugOutput.Text = ex.Message;
            }
        }

        private async void coaches_ItemClick(object sender, ItemClickEventArgs e)
        {
            coach = e.ClickedItem as Coach;

            IDictionary<string, string> parameters = train.getParameters(coach);
            string res = await Requests.makeRequestAsync(Requests.CARRIAGE_URL, parameters);

            //debugOutput.Text = coach.Prices.ToString();

            CarriageResponse resp = Factory.Instance.getCarriageResponse(res);
            places.DataContext = resp.Value.Places;
        }

        private void Seat_ItemClick(object sender, ItemClickEventArgs e)
        {
            priceOutput.Text =
                "Купити - " + (coach.Prices[0] / 100.0) + "\n" +
                "Зарезервувати - " + (coach.ReservationPrice / 100.0);
        }
    }
}
