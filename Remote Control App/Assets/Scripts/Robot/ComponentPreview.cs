using UnityEngine;
using UnityEngine.UI;

public class ComponentPreview : MonoBehaviour
{
    [SerializeField] private Text _informationText;

    [SerializeField] private string[] _information;

    public void ShowInformation(int index)
    {
        _informationText.text = _information[index];
    }
}
