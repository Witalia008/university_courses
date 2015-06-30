using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using UZTracerBGTask.src.Data;

namespace UZTracerBGTask.src.ents
{
    [JsonObject(MemberSerialization.OptIn)]
    public sealed class TrainRequest
    {
        [JsonProperty]
        public City from { get; set; }
        [JsonProperty]
        public City to { get; set; }
        [JsonProperty]
        public DateTimeOffset date { get; set; }
        [JsonProperty]
        public TimeSpan time { get; set; }
        [JsonProperty]
        public bool roundTrip { get; set; }

        public TrainRequest()
        {
            date = DateTimeOffset.Now;
        }

        public IDictionary<string, string> getParameters()
        {
            IDictionary<string, string> par = Generics.createDictStringString();

            par.Add("station_id_from", from.StationID + "");
            par.Add("station_id_till", to.StationID + "");
            par.Add("station_from", from.Name);
            par.Add("station_till", to.Name);
            par.Add("date_start", date.ToString("dd.MM.yyyy"));
            par.Add("time_from", time.ToString(@"hh\:mm"));

            //par.Add("time_dep_till", "");
            par.Add("search", "");
            if (roundTrip)
            {
                par.Add("round_trip", "1");
            }

            return par;
        }
    }

    [JsonObject(MemberSerialization.OptIn)]
    public sealed class Train
    {
        [JsonProperty("num")]
        public string Number { get; set; }

        [JsonProperty("model")]
        public int Model { get; set; }

        [JsonProperty("category")]
        public int Category { get; set; }

        [JsonProperty("from")]
        public Station From { get; set; }

        [JsonProperty("till")]
        public Station Till { get; set; }

        [JsonProperty("types")]
        public CoachType[] CoachTypes { get; set; }

        public IDictionary<string, string> getParameters(CoachType type, bool roundTrip)
        {
            IDictionary<string, string> par = Generics.createDictStringString();

            par.Add("station_id_from", From.ID + "");
            par.Add("station_id_till", Till.ID + "");
            par.Add("train", Number);
            par.Add("coach_type", type.Letter);
            par.Add("model", Model + "");
            par.Add("category", Category + "");
            par.Add("date_dep", From.Date.ToString("dd.MM.yyyy hh:mm:ss"));
            if (roundTrip)
            {
                par.Add("round_trip", "1");
            }

            return par;
        }

        public IDictionary<string, string> getParameters(Coach coach)
        {
            IDictionary<string, string> par = Generics.createDictStringString();

            par.Add("station_id_from", From.ID + "");
            par.Add("station_id_till", Till.ID + "");
            par.Add("train", Number);
            par.Add("coach_num", coach.CarriageNumber + "");
            par.Add("coach_type_id", coach.CoachTypeID + "");
            par.Add("date_dep", From.Date.ToString("dd.MM.yyyy hh:mm:ss"));
            par.Add("change_scheme", "0");

            return par;
        }

        public override string ToString()
        {
            string res =
                "Потяг " + Number + "\n" +
                From.Name + " - " + Till.Name + "\n" +
                "Відправлення: " + From.Date + "\n" +
                "Прибуття: " + Till.Date + "\n" +
                "Місця: \n";
            foreach (CoachType ct in CoachTypes)
            {
                res += "  " + ct.ToString() + "\n";
            }
            return res;
        }
    }


    [JsonObject(MemberSerialization.OptIn)]
    public sealed class TrainResponse
    {
        [JsonProperty("value")]
        public Train[] Trains { get; set; }

        [JsonProperty("error")]
        public Nullable<bool> Error { get; set; }

        [JsonProperty("data")]
        public TrainRequestData Data { get; set; }
    }

    [JsonObject(MemberSerialization.OptIn)]
    public sealed class TrainRequestData { }
}
