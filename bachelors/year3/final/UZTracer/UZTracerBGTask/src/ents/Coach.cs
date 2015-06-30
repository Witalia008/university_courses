using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using UZTracerBGTask.src.Data;

namespace UZTracerBGTask.src.ents
{
    [JsonObject(MemberSerialization.OptIn)]
    public sealed class CoachType
    {
        [JsonProperty("title")]
        public string Type { get; set; }

        [JsonProperty("letter")]
        public string Letter { get; set; }

        [JsonProperty("places")]
        public int Places { get; set; }

        public override string ToString()
        {
            return Type + " - " + Places;
        }
    }

    [JsonObject(MemberSerialization.OptIn)]
    public sealed class CoachWrapper
    {
        [JsonProperty("coach_type_id")]
        public int CoachTypeID { get; set; }

        [JsonProperty("coaches")]
        public Coach[] Coaches { get; set; }

        [JsonProperty("places_allowed")]
        public int PlacesAllowed { get; set; }

        [JsonProperty("places_max")]
        public int PlacesMax { get; set; }
    }

    [JsonObject(MemberSerialization.OptIn)]
    public sealed class Coach {
        [JsonProperty("num")]
        public int CarriageNumber { get; set; }

        [JsonProperty("coach_type_id")]
        public int CoachTypeID { get; set; }

        [JsonProperty("coach_class")]
        public string CoachClass { get; set; }

        [JsonProperty("has_bedding")]
        public bool HasBedding { get; set; }

        [JsonProperty("services")]
        public dynamic[] Services { get; set; }

        [JsonProperty("places_cnt")]
        public int PlacesCount { get; set; }

        [JsonProperty("prices")]
        public int[] Prices { get; set; }

        [JsonProperty("reserve_price")]
        public int ReservationPrice { get; set; }

        [JsonProperty("allow_bonus")]
        public bool AllowBonus { get; set; }

        public override string ToString()
        {
            return 
                "Вагон - " + CarriageNumber + "\n" +
                "Місць - " + PlacesCount;
        }
    }

    [JsonObject(MemberSerialization.OptIn)]
    public sealed class CarriagePlaces
    {
        private IList<IList<int>> places = null;
        [JsonProperty("places")]
        public IList<IList<int>> Places
        {
            get
            {
                if (places == null)
                {
                    places = Generics.createListListInt();
                }
                return places;
            }
            set
            {
                places = value;
            }
        }
    }

    [JsonObject(MemberSerialization.OptIn)]
    public sealed class CoachResponse
    {
        [JsonProperty("value")]
        public CoachWrapper Wrapper { get; set; }

        [JsonProperty("error")]
        public Nullable<bool> Error { get; set; }

        [JsonProperty("data")]
        public CoachRequestData Data { get; set; }
    }

    [JsonObject(MemberSerialization.OptIn)]
    public sealed class CarriageResponse
    {
        [JsonProperty("value")]
        public CarriagePlaces Value { get; set; }

        [JsonProperty("error")]
        public Nullable<bool> Error { get; set; }

        [JsonProperty("data")]
        public CarriageRequestData Data { get; set; }
    }

    [JsonObject(MemberSerialization.OptIn)]
    public sealed class CarriageRequestData {}

    [JsonObject(MemberSerialization.OptIn)]
    public sealed class CoachRequestData { }
}
