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
using Windows.UI.Notifications;
using Windows.UI.Popups;
using Windows.Data.Xml.Dom;
using Windows.ApplicationModel.Background;
using UZTracer.Common;
using UZTracerBGTask;
using UZTracerBGTask.src;
using UZTracerBGTask.src.Data;
using UZTracerBGTask.src.ents;
using UZTracerBGTask.src.Net;
using System.Collections.ObjectModel;
using Newtonsoft.Json;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=391641

namespace UZTracer
{
    public enum Mode
    {
        NEW, INFO, EDIT
    }

    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        private NavigationHelper navigationHelper;
        public static ObservableCollection<Ticket> tickets { get; set; }
        public static ObservableCollection<Request> requests { get; set; }
        private Ticket holdedTicket = null;
        private Request holdedRequest = null;
        public static ObservableCollection<City> sugg { get; set; }
        private TrainRequest trainRequest = new TrainRequest();

        public MainPage()
        {
            this.InitializeComponent();

            this.NavigationCacheMode = NavigationCacheMode.Required;

            this.navigationHelper = new NavigationHelper(this);
            this.navigationHelper.LoadState += navigationHelper_LoadState;
            this.navigationHelper.SaveState += navigationHelper_SaveState;

            IEnumerable<Ticket> data = AppDataManager.RetrieveTickets();
            tickets =
                data == null 
                ? new ObservableCollection<Ticket>()
                : new ObservableCollection<Ticket>(data);

            IEnumerable<Request> data1 = AppDataManager.RetrieveRequests();
            requests =
                data1 == null
                ? new ObservableCollection<Request>()
                : new ObservableCollection<Request>(data1);

            sugg = new ObservableCollection<City>();
            fromBox.DataContext = this;
            toBox.DataContext = this;
            trainReqBox.DataContext = trainRequest;
        }

        void navigationHelper_SaveState(object sender, SaveStateEventArgs e)
        {
        }

        void navigationHelper_LoadState(object sender, LoadStateEventArgs e)
        {
        }
        
        #region NavigationHelper registration

        /// <summary>
        /// Invoked when this page is about to be displayed in a Frame.
        /// </summary>
        /// <param name="e">Event data that describes how this page was reached.
        /// This parameter is typically used to configure the page.</param>
        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            // TODO: Prepare page for display here.

            // TODO: If your application contains multiple pages, ensure that you are
            // handling the hardware Back button by registering for the
            // Windows.Phone.UI.Input.HardwareButtons.BackPressed event.
            // If you are using the NavigationHelper provided by some templates,
            // this event is handled for you.
            navigationHelper.OnNavigatedTo(e);

            ticketsList.DataContext = null;
            ticketsList.DataContext = tickets;
            AppDataManager.SaveTickets(tickets);

            requestsList.DataContext = null;
            requestsList.DataContext = requests;
            AppDataManager.SaveRequests(requests);

            Notification.ClearBadge();
        }

        protected override void OnNavigatedFrom(NavigationEventArgs e)
        {
            navigationHelper.OnNavigatedFrom(e);
        }

        #endregion

        private void ListViewItem_Holding(object sender, HoldingRoutedEventArgs e)
        {
            FrameworkElement senderElement = sender as FrameworkElement;
            FlyoutBase flyoutBase = FlyoutBase.GetAttachedFlyout(senderElement);
            flyoutBase.ShowAt(senderElement);

            switch (mainPivot.SelectedIndex) {
                case 0:
                    holdedTicket = senderElement.DataContext as Ticket;
                    break;
                case 1:
                    holdedRequest = senderElement.DataContext as Request;
                    break;
            }
        }

        public static BackgroundTaskRegistration RegisterBackGroundTask(
            string taskEntryPoint, 
            string taskName,
            IBackgroundTrigger trigger,
            IBackgroundCondition condition)
        {
            foreach (var task in BackgroundTaskRegistration.AllTasks)
            {
                if (task.Value.Name == taskName)
                {
                    return (BackgroundTaskRegistration)task.Value;
                }
            }

            var builder = new BackgroundTaskBuilder();

            builder.Name = taskName;
            builder.TaskEntryPoint = taskEntryPoint;
            builder.SetTrigger(trigger);

            if (condition != null)
            {
                builder.AddCondition(condition);
            }

            return builder.Register();
        }

        private async void Grid_Loaded(object sender, RoutedEventArgs e)
        {
            TimeTrigger trigger = new TimeTrigger(15, false);
            SystemCondition condition = new SystemCondition(SystemConditionType.InternetAvailable);
            await BackgroundExecutionManager.RequestAccessAsync();
            string entryPoint = typeof(BackgroundTask).FullName;
            string taskName = "UZTracer Updates";
            BackgroundTaskRegistration task = RegisterBackGroundTask(entryPoint, taskName, trigger, null);
        }

        private void Add_Click(object sender, RoutedEventArgs e)
        {
            switch (mainPivot.SelectedIndex)
            {
                case 0:
                    this.Frame.Navigate(typeof(TicketPage), Mode.NEW + "&{}");
                    break;
                case 1:
                    this.Frame.Navigate(typeof(RequestPage), Mode.NEW + "&{}");
                    break;
            }
        }

        private void Remove_Click(object sender, RoutedEventArgs e)
        {
            switch (mainPivot.SelectedIndex)
            {
                case 0:
                    tickets.Remove(holdedTicket);
                    break;
                case 1:
                    requests.Remove(holdedRequest);
                    break;
            }
        }

        private void Edit_Click(object sender, RoutedEventArgs e)
        {
            switch (mainPivot.SelectedIndex)
            {
                case 0:
                    this.Frame.Navigate(typeof(TicketPage), Mode.EDIT + "&" + tickets.IndexOf(holdedTicket));
                    break;
                case 1:
                    this.Frame.Navigate(typeof(RequestPage), Mode.EDIT + "&" + requests.IndexOf(holdedRequest));
                    break;
            }
        }

        private void Info_Click(object sender, RoutedEventArgs e)
        {
            switch (mainPivot.SelectedIndex)
            {
                case 0:
                    this.Frame.Navigate(typeof(TicketPage), Mode.INFO + "&" + JsonConvert.SerializeObject(holdedTicket));
                    break;
                case 1:
                    this.Frame.Navigate(typeof(RequestPage), Mode.INFO + "&" + JsonConvert.SerializeObject(holdedRequest));
                    break;
            }
        }

        public async void suggestions_TextChanged(AutoSuggestBox sender, AutoSuggestBoxTextChangedEventArgs args)
        {
            if (args.Reason == AutoSuggestionBoxTextChangeReason.UserInput && sender.Text.Length > 1)
            {
                sugg.Clear();
                string data = await Requests.makeRequestAsync(
                    Requests.CITY_URL + sender.Text,
                    new Dictionary<string, string>());

                CityResponse response = Factory.Instance.getCityResponse(data);
                foreach (City c in response.Cities)
                {
                    sugg.Add(c);
                }
            }
        }

        private void suggestBox_SuggestionChosen(AutoSuggestBox sender, AutoSuggestBoxSuggestionChosenEventArgs args)
        {
            switch (sender.Tag.ToString())
            {
                case "from":
                    trainRequest.from = args.SelectedItem as City;
                    break;
                case "to":
                    trainRequest.to = args.SelectedItem as City;
                    break;
            }
        }

        private async void Search_Click(object sender, RoutedEventArgs e)
        {
            if (trainRequest.from.StationID != 0 && trainRequest.to.StationID != 0)
            {
                //debugOutput.Text = trainRequest.getParameters().ToQueryString();
                string data = await Requests.makeRequestAsync(
                    Requests.TRAIN_URL, trainRequest.getParameters());
                //debugOutput.Text = data;
                TrainResponse resp = Factory.Instance.getTrainResponse(data);
                results.DataContext = null;
                results.DataContext = resp.Trains;
            }
        }

        private void results_ItemClick(object sender, ItemClickEventArgs e)
        {
            //debugOutput.Text = (e.ClickedItem as Train).ToString();
            this.Frame.Navigate(typeof(TrainPage), e.ClickedItem as Train);
        }

        private async void Help_Click(object sender, RoutedEventArgs e)
        {
            await new MessageDialog("Created by\nWitalia\n02.2015 (c)").ShowAsync();
        }

        private void ItemList_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ListView lv = sender as ListView;
            if (e.AddedItems.Count > 0)
            {
                switch (mainPivot.SelectedIndex)
                {
                    case 0:
                        holdedTicket = e.AddedItems[0] as Ticket;
                        break;
                    case 1:
                        holdedRequest = e.AddedItems[0] as Request;
                        break;
                }
            }
        }
    }
}
