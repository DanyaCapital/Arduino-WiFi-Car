using System.Collections;
using System.Net.Sockets;
using System.Text;
using UnityEngine;

public class RemoteControl : MonoBehaviour
{
    [SerializeField] private DebugLog _log;
    [SerializeField] private RobotPreview _robot;

    private TcpClient _client = new TcpClient();
    private NetworkStream _stream;

    private string _ipAddress = "192.168.4.1";

    private int _port = 80;
    private bool _gripped;
    private void Start()
    {
        Application.targetFrameRate = 0;
        QualitySettings.vSyncCount = 0;
    }
    public void Connect()
    {
        StartCoroutine(Connecting());
    }

    private IEnumerator Connecting()
    {
        for (int i = 0; i < 3; i++)
        {
            _log.AddMessage($"Идет подключение к роботу{new string('.', i)}");

            yield return new WaitForSeconds(0.33f);
        }

        try
        {
            _client.Connect(_ipAddress, _port);
            _stream = _client.GetStream();

            _log.AddMessage("Успешно!");
        }
        catch
        {
            _log.AddMessage("Произошла ошибка при подключении");
        }
    }

    private void DetectCommand(string command)
    {
        switch (command)
        {
            case "S":
                _log.AddMessage("Движение остановлено");
                _robot.Lights(true, false);
                break;
            case "F":
                _log.AddMessage("Движение вперед");
                break;
            case "B":
                _log.AddMessage("Движение назад");
                break;
            case "L":
                _log.AddMessage("Движение влево");
                break;
            case "R":
                _log.AddMessage("Движение вправо");
                break;
            case "Y":
                _log.AddMessage("Включены фары");
                break;
            case "I":
                _log.AddMessage("Выключены фары");
                break;
            case "P":
                _log.AddMessage("Захват поднялся");
                break;
            case "O":
                _log.AddMessage("Захват опустился");
                break;
            case "K":
                _log.AddMessage("Захват сжат");
                break;
            case "J":
                _log.AddMessage("Захват расжат");
                break;
            default:
                _robot.Lights(false, false);
                break;
        }
    }

    public void SendRemoteCommand(string command)
    {
        try
        {
            DetectCommand(command);

            byte[] data = Encoding.ASCII.GetBytes(command);
            _stream.Write(data, 0, data.Length);
        }
        catch
        {
            _log.AddMessage("Произошла ошибка при отправке команды");
        }
    }

    public void SendGripCommand()
    {
        _gripped = !_gripped;

        string command = _gripped ? "K" : "J";
        SendRemoteCommand(command);
    }
}
