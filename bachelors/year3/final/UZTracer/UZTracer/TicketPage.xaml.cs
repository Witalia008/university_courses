using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Collections.ObjectModel;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using UZTracer.Common;
using UZTracerBGTask.src.Data;
using UZTracerBGTask.src.Net;
using UZTracerBGTask.src.ents;
using System.Collections;
using Newtonsoft.Json;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkID=390556

namespace UZTracer
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class TicketPage : Page
    {
        private NavigationHelper navigationHelper;

        public ObservableCollection<City> sugg { get; set; }
        public Ticket ticket { get; set; }
        private Mode mode;
        private CityResponse response;

        public TicketPage()
        {
            this.InitializeComponent();

            this.NavigationCacheMode = NavigationCacheMode.Required;

            this.navigationHelper = new NavigationHelper(this);
            this.navigationHelper.LoadState += navigationHelper_LoadState;
            this.navigationHelper.SaveState += navigationHelper_SaveState;

            sugg = new ObservableCollection<City>();
            fromBox.DataContext = this;
            toBox.DataContext = this;
        }

        void navigationHelper_SaveState(object sender, SaveStateEventArgs e)
        {
            //throw new NotImplementedException();
        }

        void navigationHelper_LoadState(object sender, LoadStateEventArgs e)
        {
            //throw new NotImplementedException();
        }

        #region NavigationHelper registration
        /// <summary>
        /// Invoked when this page is about to be displayed in a Frame.
        /// </summary>
        /// <param name="e">Event data that describes how this page was reached.
        /// This parameter is typically used to configure the page.</param>
        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            string param = e.Parameter.ToString();
            int pos = param.IndexOf("&");
            string action = param.Substring(0, pos);
            param = param.Substring(pos + 1);
            mode = (Mode) Enum.Parse(typeof(Mode), action.ToUpper());
            switch (mode)
            {
                case Mode.NEW:
                    ticket = new Ticket();
                    break;
                case Mode.INFO:
                    ticket = JsonConvert.DeserializeObject<Ticket>(param);
                    break;
                case Mode.EDIT:
                    ticket = MainPage.tickets.ElementAt(int.Parse(param));
                    break;
            }
            
            ticketInfo.DataContext = ticket;
            if (mode != Mode.NEW)
            {
                toBox.Text = ticket.to.Name;
                fromBox.Text = ticket.from.Name;
            }

            //debugOutput.Text = action + "\n" + typeof(TicketPage);
            navigationHelper.OnNavigatedTo(e);
        }

        protected override void OnNavigatedFrom(NavigationEventArgs e)
        {
            ticket = null;
            navigationHelper.OnNavigatedFrom(e);
        }
        #endregion

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            if (mode != Mode.INFO)
            {
                DateTimeOffset now = DateTimeOffset.Now;
                DateTimeOffset dep = ticket.departure.date + ticket.departure.time;
                DateTimeOffset arr = ticket.arrival.date + ticket.arrival.time;
                if (ticket.from.StationID == 0 || ticket.to.StationID == 0
                    || dep < now || arr < now || arr < dep)
                {
                    //debugOutput.Text = "Wrong data entered";
                }
            }

            if (mode == Mode.NEW)
            {
                MainPage.tickets.Add(ticket);
            }

            //this.Frame.Navigate(typeof(MainPage));
            this.Frame.GoBack();
        }

        public async void suggestions_TextChanged(AutoSuggestBox sender, AutoSuggestBoxTextChangedEventArgs args)
        {
            if (args.Reason == AutoSuggestionBoxTextChangeReason.UserInput && sender.Text.Length > 1)
            {
                sugg.Clear();
                string data = await Requests.makeRequestAsync(
                    Requests.CITY_URL + sender.Text,
                    new Dictionary<string, string>());

                response = Factory.Instance.getCityResponse(data);
                foreach (City c in response.Cities)
                {
                    sugg.Add(c);
                }
            }
        }

        private void suggestBox_SuggestionChosen(AutoSuggestBox sender, AutoSuggestBoxSuggestionChosenEventArgs args)
        {
            if (sender.Tag.ToString() == "from")
            {
                ticket.from = args.SelectedItem as City;
            }
            else
            {
                ticket.to = args.SelectedItem as City;
            }
        }
    }
}
