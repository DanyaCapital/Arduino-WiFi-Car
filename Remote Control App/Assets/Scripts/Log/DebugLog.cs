using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class DebugLog : MonoBehaviour
{
    [SerializeField] private Text _uiText;

    private List<string> _messages = new List<string>();

    private const int _maxMessages = 3;

    public void AddMessage(string message)
    {
        _messages.Add(message);

        if (_messages.Count > _maxMessages)
        {
            _messages.RemoveAt(0);
        }

        UpdateUIText();
    }

    private void UpdateUIText()
    {
        _uiText.text = string.Join("\n", _messages);
    }
}
