using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.Foundation;
using System.Net;
using System.Net.Http;
using System.IO;
using System.Text.RegularExpressions;
using UZTracerBGTask.src.Data;
using UZTracerBGTask.src.ents;
using System.Reflection;
//using Windows.Web.Http;

namespace UZTracerBGTask.src.Net
{

    public static class Requests
    {
        public static string CITY_URL {
            get {
                return "http://www.plategka.com/uk/uzd/station/"; 
            }
        }
        public static string TRAIN_URL {
            get {
                return "http://www.plategka.com/uk/uzd/search/"; 
            }
        }
        public static string COACH_URL {
            get {
                return "http://www.plategka.com/uk/uzd/coaches/";
            }
        }
        public static string CARRIAGE_URL {
            get {
                return "http://www.plategka.com/uk/uzd/coach/";
            }
        }
        private static HttpClientHandler handler = null;
        private static HttpClientHandler Handler
        {
            get
            {
                if (handler == null)
                {
                    handler = new HttpClientHandler();
                    handler.CookieContainer = new CookieContainer();
                }
                return handler;
            }
            set
            {
                handler = value;
            }
        }
        private static HttpClient client = null;
        private static HttpClient Client
        {
            get
            {
                if (client == null)
                {
                    client = new HttpClient(Handler);
                }
                return client;
            }
            set
            {
                client = value;
            }
        }

        public static IAsyncOperation<string> makeRequestAsync(string uri,
            IDictionary<string, string> parameters)
        {
            return makeRequestAsyncHelper(uri, parameters).AsAsyncOperation();
        }

        private static async Task<string> makeRequestAsyncHelper(string uri,
            IDictionary<string, string> parameters)
        {
            Client.DefaultRequestHeaders.Add("GV-Ajax", "1");
            Client.DefaultRequestHeaders.Add("GV-Referer", "http://www.plategka.com/kvitkiv-na-potjag-za-dopomogoju-internetu");
            Client.DefaultRequestHeaders.Add("GV-Screen", "1360x768");

            FormUrlEncodedContent content = new FormUrlEncodedContent(parameters);
            HttpResponseMessage resp = await Client.PostAsync(uri, content);
            return await resp.Content.ReadAsStringAsync();
        }

        public static string ToQueryString(this IDictionary<string, string> parameters)
        {
            return String.Join("&", parameters.Select(p => p.Key + "=" + Uri.EscapeDataString(p.Value)).ToArray());
        }
    }
}
