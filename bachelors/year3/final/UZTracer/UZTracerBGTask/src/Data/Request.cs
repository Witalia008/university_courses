using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using UZTracerBGTask.src.ents;

namespace UZTracerBGTask.src.Data
{
    [JsonObject(MemberSerialization.Fields)]
    public sealed class TimePair
    {
        public TimeSpan since { get; set; }
        public TimeSpan till { get; set; }

        public TimePair()
        {
            since = new TimeSpan(0, 0, 0);
            till = new TimeSpan(23, 59, 59);
        }

        public bool checkInside(TimeSpan time)
        {
            return time >= since && time <= till;
        }
    }

    [JsonObject(MemberSerialization.Fields)]
    public sealed class DatePair
    {
        public DateTimeOffset since { get; set; }
        public DateTimeOffset till { get; set; }

        public DatePair()
        {
            since = DateTimeOffset.Now.Date;
            till = DateTimeOffset.Now.Date;
        }

        public bool checkInside(DateTimeOffset date)
        {
            return date.Date >= since && date.Date <= till;
        }
    }

    [JsonObject(MemberSerialization.Fields)]
    public sealed class SeatProps
    {
        public bool mayLower { get; set; }
        public bool mayUpper { get; set; }
        public bool maySide { get; set; }
        public bool mayToilet { get; set; }

        public SeatProps()
        {
            mayLower = true;
            maySide = true;
            mayToilet = true;
            mayUpper = true;
        }
    }

    [JsonObject(MemberSerialization.Fields)]
    public sealed class Request
    {
        public City from { get; set; }
        public City to { get; set; }
        public DatePair depDateFrame { get; set; }
        public TimePair depTimeFrame { get; set; }
        public TimePair arrTimeFrame { get; set; }
        public CoachType coachType { get; set; }
        public SeatProps seatProps { get; set; }
        public int maxPrice { get; set; }
        public TimeSpan maxTravelTime { get; set; }
        //[JsonIgnore]
        private IDictionary<string, int> _avail = null;
        public IDictionary<string, int> available
        {
            get
            {
                if (_avail == null)
                {
                    _avail = Generics.createDictStringInt();
                }
                return _avail;
            }
            set
            {
                _avail = value;
            }
        }

        public Request()
        {
            from = new City();
            to = new City();
            depDateFrame = new DatePair();
            depTimeFrame = new TimePair();
            arrTimeFrame = new TimePair();
            seatProps = new SeatProps();
            maxPrice = int.MaxValue;
            maxTravelTime = new TimeSpan(12, 0, 0);
        }

        public override string ToString()
        {
            return
                "Звідки - " + from + "\n" +
                "Куди - " + to + "\n" +
                "Дата - " + depDateFrame.since.ToString("d") +
                " - " + depDateFrame.till.ToString("d");
        }
    }
}
