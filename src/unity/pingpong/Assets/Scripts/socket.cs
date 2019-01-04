using System;
using System.IO;
using System.Net;
using System.Net.Sockets;

namespace PingPong.Net
{
    public class Server
    {
        private TcpListener listener;
        private Socket soc;
        private NetworkStream s;
        public StreamReader sr;
        public StreamWriter sw;
        public BinaryWriter bw;

        public Server(String host = "127.0.0.1", Int32 port = 40040)
        {

            listener = new TcpListener(IPAddress.Parse(host), port);
            listener.Start();

            soc = listener.AcceptSocket(); // blocks, accpet 1 client
            s = new NetworkStream(soc);
        }

        ~Server()
        {
            s.Close();
            soc.Close();
        }
    }

    public class Client : SystemException
    {
        private TcpClient c;
        public NetworkStream stream;
        //    public StreamReader sr;
        //    public StreamWriter sw;
        //    public BinaryWriter bw;

        public Client(string host = "127.0.0.1", Int32 port = 40040)
        {
            c = new TcpClient(host, port);
            stream = c.GetStream();
            //         sr = new StreamReader(s);
            //         sw = new StreamWriter(s);
            //         bw = new BinaryWriter(s);
            //         sw.AutoFlush = false;
        }

        //Converts the data size to byte array and put result to the fullBytes array
        private void ByteLengthToFrameByteArray(int byteLength, byte[] fullBytes)
        {
            //Clear old data
            Array.Clear(fullBytes, 0, fullBytes.Length);
            //Convert int to bytes
            byte[] bytesToSendCount = BitConverter.GetBytes(byteLength);
            //Copy result to fullBytes
            bytesToSendCount.CopyTo(fullBytes, 0);
        }

        public void SendInt(int num)
        {
            byte[] numByteLength = new byte[15];
            ByteLengthToFrameByteArray(num, numByteLength);

            stream.Write(numByteLength, 0, numByteLength.Length);
        }

        ~Client()
        {
            stream.Close();
            c.Close();
        }
    }
}