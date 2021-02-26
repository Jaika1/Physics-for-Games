using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class OrbitalCamera : MonoBehaviour
{
    public Transform Target;
    public Vector3 Offset = new Vector3(0, 1, 0);
    public float FollowMax = 5.0f;
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

        angles.x = Mathf.Clamp(angles.x - dx, -60, 85);
        angles.y += dy;

        transform.eulerAngles = angles;


        float backDist = FollowMax;
        Ray r = new Ray(Target.position + Offset, -transform.forward);
        RaycastHit hitInfo;
        if (Physics.Raycast(r, out hitInfo, FollowMax))
            backDist = Mathf.Min(hitInfo.distance - 0.1f, FollowMax);

        transform.position = Target.position + Offset - backDist * transform.forward;
    }
}
