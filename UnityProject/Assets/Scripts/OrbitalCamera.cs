using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class OrbitalCamera : MonoBehaviour
{
    public Transform Target;
    public float Sensitivity = 2.0f;

    Vector3 angles;

    void Awake()
    {
        angles = transform.eulerAngles;
        Cursor.lockState = CursorLockMode.Locked;
    }

    // Update is called once per frame
    void Update()
    {
        float dx = Input.GetAxis("Mouse Y") * Sensitivity;
        float dy = Input.GetAxis("Mouse X") * Sensitivity;

        angles.x = Mathf.Clamp(angles.x - dx, -20, 85);
        angles.y += dy;

        transform.eulerAngles = angles;

        Ray r = new Ray(Target.position, -transform.forward);
        RaycastHit hitInfo;
        Physics.Raycast(r, out hitInfo);

        transform.position = Target.position - Mathf.Min(hitInfo.distance - 0.1f, 6.0f) * transform.forward;
    }

    private void OnDrawGizmos()
    {
    }
}
