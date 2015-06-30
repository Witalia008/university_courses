using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UZTracerBGTask.src.ents;
using Newtonsoft.Json;

namespace UZTracerBGTask.src.Data
{
    [JsonObject(MemberSerialization.Fields)]
    public sealed class TimePoint
    {
        public TimeSpan time { get; set; }
        public DateTimeOffset date { get; set; }

        public TimePoint()
        {
            date = DateTimeOffset.Now;
            time = date.TimeOfDay;
        }

        public DateTimeOffset GetDateTime() {
            return date.Date + time;
        }

        public override string ToString()
        {
            return date.ToString("d") + " " + time.ToString(@"hh\:mm\:ss");
        }
    }

    [JsonObject(MemberSerialization.Fields)]
    public sealed class Ticket
    {
        public City from { get; set; }
        public City to { get; set; }
        public TimePoint departure { get; set; }
        public TimePoint arrival { get; set; }
        public bool notifyBeforeDeparture { get; set; }

        public Ticket()
        {
            from = new City();
            to = new City();
            arrival = new TimePoint();
            departure = new TimePoint();
        }

        public override string ToString()
        {
            return 
                "Звідки: " + from + "\n" + 
                "Куди: " + to + "\n" +
                "Відправлення: " + departure + "\n" +
                "Прибуття: " + arrival + "\n" +
                "Нагадування: " + (notifyBeforeDeparture ? "так" : "ні");
        }
    }
}
