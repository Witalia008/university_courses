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
using UZTracer.Common;
using System.Collections.ObjectModel;
using UZTracerBGTask.src.Net;
using UZTracerBGTask.src.ents;
using UZTracerBGTask.src.Data;
using Newtonsoft.Json;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkID=390556

namespace UZTracer
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class RequestPage : Page
    {
        private NavigationHelper navigationHelper;

        public ObservableCollection<City> sugg { get; set; }
        private CityResponse response;
        private Mode mode;
        private Request request;

        public RequestPage()
        {
            this.InitializeComponent();

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

        private void navigationHelper_LoadState(object sender, LoadStateEventArgs e)
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
            mode = (Mode)Enum.Parse(typeof(Mode), action.ToUpper());
            switch (mode)
            {
                case Mode.NEW:
                    request = new Request();
                    break;
                case Mode.INFO:
                    request = JsonConvert.DeserializeObject<Request>(param);
                    break;
                case Mode.EDIT:
                    request = MainPage.requests.ElementAt(int.Parse(param));
                    break;
            }

            requestInfo.DataContext = request;
            if (mode != Mode.NEW)
            {
                toBox.Text = request.to.Name;
                fromBox.Text = request.from.Name;
            }

            //debugOutput.Text = action + "\n" + typeof(TicketPage);
            navigationHelper.OnNavigatedTo(e);
        }

        protected override void OnNavigatedFrom(NavigationEventArgs e)
        {
            request = null;
            navigationHelper.OnNavigatedFrom(e);
        }
        #endregion

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
                request.from = args.SelectedItem as City;
            }
            else
            {
                request.to = args.SelectedItem as City;
            }
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            if (mode != Mode.INFO)
            {
                DateTimeOffset now = DateTimeOffset.Now;
                // TODO: Check if data is correct
            }

            if (mode == Mode.NEW)
            {
                MainPage.requests.Add(request);
            }

            if (mode == Mode.EDIT)
            {
                request.available.Clear();
            }

            //this.Frame.Navigate(typeof(MainPage));
            this.Frame.GoBack();
        }

        private void ComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            // TODO: handle this thing
        }
    }
}
