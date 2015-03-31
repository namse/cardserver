using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;
using System.Text;
using WebSocketSharp;
using System.Runtime.InteropServices;
namespace DummyClient
{

    static class Program
    {

        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        static extern bool AllocConsole();

        /// <summary>
        /// 해당 응용 프로그램의 주 진입점입니다.
        /// </summary>
        [STAThread]
        static void Main()
        {
            AllocConsole();
            using (var ws = new WebSocket("ws://localhost:3000/"))
            {
                ws.OnMessage += (sender, e) =>
                  Console.WriteLine("Laputa says: " + e.Data);

                ws.Connect();
                ws.Send("abccacb");
                Console.ReadKey(true);
            }
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
        }
    }
}
