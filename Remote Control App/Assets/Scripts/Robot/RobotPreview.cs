using System.Collections;
using UnityEngine;

public class RobotPreview : MonoBehaviour
{
    [Header("Required")]
    [SerializeField] private RemoteControl _remote;
    [SerializeField] private float _rotationSpeed;

    [Header("Lights Objects")]
    [SerializeField] private GameObject[] _lightW;
    [SerializeField] private GameObject[] _lightR;

    private Quaternion _targetRotation;

    private bool _forwardLightOn;

    private void Start()
    {
        _targetRotation = transform.rotation;
    }

    public void Rotate(float angle)
    {
        _targetRotation *= Quaternion.Euler(0, angle, 0);
    }

    private void Update()
    {
        transform.rotation = Quaternion.Lerp(transform.rotation, _targetRotation, Time.deltaTime * _rotationSpeed);
    }

    public void ForwardLights()
    {
        Lights(false, true);
    }

    public void Lights(bool on, bool forward)
    {
        if (forward)
        {
            _forwardLightOn = !_forwardLightOn;

            for (int i = 0; i < _lightW.Length; i++)
            {
                _lightW[i].SetActive(_forwardLightOn);
            }

            string command = _forwardLightOn ? "Y" : "I";
            _remote.SendRemoteCommand(command);
        }
        else
        {
            if (on)
            {
                StartCoroutine(BackwardLightsOn());
            }
            else
            {
                for (int i = 0; i < _lightR.Length; i++)
                {
                    _lightR[i].SetActive(on);
                }
            }
        }
    }

    private IEnumerator BackwardLightsOn()
    {
        for (int i = 0; i < _lightW.Length; i++)
        {
            _lightR[i].SetActive(true);
        }

        yield return new WaitForSeconds(0.3f);

        for (int i = 0; i < _lightW.Length; i++)
        {
            _lightR[i].SetActive(false);
        }
    }

}
