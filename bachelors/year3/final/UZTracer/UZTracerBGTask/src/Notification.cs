using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.UI.Notifications;
using Windows.Data.Xml.Dom;

namespace UZTracerBGTask.src
{
    public sealed class Notification
    {
        public static void SendToast(
            string head,
            string text,
            DateTimeOffset dueTime,
            string launch)
        {
            ToastTemplateType toastTemplate = ToastTemplateType.ToastText02;
            XmlDocument toastXml = ToastNotificationManager.GetTemplateContent(toastTemplate);
            XmlNodeList toastTextElements = toastXml.GetElementsByTagName("text");
            toastTextElements[0].AppendChild(toastXml.CreateTextNode(head));
            toastTextElements[1].AppendChild(toastXml.CreateTextNode(text));

            IXmlNode toastNode = toastXml.SelectSingleNode("/toast");
            XmlElement audio = toastXml.CreateElement("audio");
            audio.SetAttribute("src", "ms-winsoundevent:Notification.IM");

            toastNode.AppendChild(audio);

            if (launch != null)
            {
                ((XmlElement)toastNode).SetAttribute("launch", launch);
            }
            
            ScheduledToastNotification scheduledToast = new ScheduledToastNotification(toastXml, dueTime);
            scheduledToast.Id = "Future_Toast";
            ToastNotificationManager.CreateToastNotifier().AddToSchedule(scheduledToast);
        }

        public static void SendTile(string text, DateTimeOffset expiration)
        {
            XmlDocument tileXml = TileUpdateManager.
                GetTemplateContent(TileTemplateType.TileWide310x150BlockAndText01);
            XmlNodeList tileTextAttributes = tileXml.GetElementsByTagName("text");
            tileTextAttributes[0].InnerText = text;

            XmlDocument squareTileXml = TileUpdateManager.
                GetTemplateContent(TileTemplateType.TileSquare150x150Text01);
            XmlNodeList squareTileTextAttributes = squareTileXml.GetElementsByTagName("text");
            squareTileTextAttributes[0].InnerText = text;

            IXmlNode node = tileXml.ImportNode(squareTileXml.GetElementsByTagName("binding").Item(0), true);
            tileXml.GetElementsByTagName("visual").Item(0).AppendChild(node);

            TileNotification tileNotification = new TileNotification(tileXml);
            tileNotification.ExpirationTime = expiration;
            TileUpdateManager.CreateTileUpdaterForApplication().Update(tileNotification);
        }

        public static void ClearTile()
        {
            TileUpdateManager.CreateTileUpdaterForApplication().Clear();
        }

        public static void UpdateBadge(int number)
        {
            XmlDocument badgeXml = BadgeUpdateManager.GetTemplateContent(BadgeTemplateType.BadgeNumber);
            XmlElement badgeElement = (XmlElement)badgeXml.SelectSingleNode("/badge");
            badgeElement.SetAttribute("value", "" + number);

            BadgeNotification badge = new BadgeNotification(badgeXml);
            BadgeUpdateManager.CreateBadgeUpdaterForApplication().Update(badge);
        }

        public static void ClearBadge()
        {
            BadgeUpdateManager.CreateBadgeUpdaterForApplication().Clear();
        }
    }
}
