using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json.Linq;
using Newtonsoft.Json;

namespace UZTracerBGTask.src.ents
{
    public class Factory
    {
        private static Factory instance;

        private Factory() { }

        public static Factory Instance
        {
            get
            {
                if (instance == null)
                {
                    instance = new Factory();
                }
                return instance;
            }
        }

        
        public CityResponse getCityResponse(string json)
        {
            return JsonConvert.DeserializeObject<CityResponse>(json);
        }

        public TrainResponse getTrainResponse(string json)
        {
            return JsonConvert.DeserializeObject<TrainResponse>(json);
        }

        public CarriageResponse getCarriageResponse(string json)
        {
            return JsonConvert.DeserializeObject<CarriageResponse>(json);
        }

        public CoachResponse getCoachResponse(string json)
        {
            return JsonConvert.DeserializeObject<CoachResponse>(json);
        }
    }
}
