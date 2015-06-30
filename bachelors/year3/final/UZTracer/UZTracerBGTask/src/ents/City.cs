using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace UZTracerBGTask.src.ents
{
    [JsonObject(MemberSerialization.OptIn)]
    public sealed class City
    {
        [JsonProperty("station_id")]
        public int StationID { get; set; }

        [JsonProperty("title")]
        public string Name { get; set; }

        public override string ToString()
        {
            return Name;
        }
    }

    [JsonObject(MemberSerialization.OptIn)]
    public sealed class Station
    {
        [JsonProperty("station_id")]
        public int ID { get; set; }

        [JsonProperty("station")]
        public string Name { get; set; }

        //[JsonProperty("date")]
        //public int dateValue { get; set; }

        [JsonProperty("date")]
        public DateTimeOffset Date { get; set; }
    }

    [JsonObject(MemberSerialization.OptIn)]
    public sealed class CityResponse
    {
        [JsonProperty("value")]
        public City[] Cities { get; set; }

        [JsonProperty("error")]
        public Nullable<bool> Error { get; set; }

        [JsonProperty("data")]
        public CityRequestData Data { get; set; }
    }

    [JsonObject(MemberSerialization.OptIn)]
    public sealed class CityRequestData
    {
        [JsonProperty("req_text")]
        public string[] Text { get; set; }
    }
}
