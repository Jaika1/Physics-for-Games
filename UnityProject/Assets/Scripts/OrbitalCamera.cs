using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class OrbitalCamera : MonoBehaviour
{
    public Transform Target;
    public float HeightOffset = 1.0f;
    public float MaxFollowDistance = 5.0f;
    public float Sensitivity = 2.0f;

    Vector3 angles;
    LayerMask playerLayer;

    void Awake()
    {
        angles = transform.eulerAngles;
        Cursor.lockState = CursorLockMode.Locked;
        playerLayer = LayerMask.GetMask("Player");
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.R)) SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex);

        float dx = Input.GetAxis("Mouse Y") * Sensitivity;
        float dy = Input.GetAxis("Mouse X") * Sensitivity;

        angles.x = Mathf.Clamp(angles.x - dx, -60, 85);
        angles.y += dy;

        transform.eulerAngles = angles;


        float backDist = MaxFollowDistance;
        Ray r = new Ray(Target.position + HeightOffset * Vector3.up, -transform.forward);
        RaycastHit hitInfo;
        if (Physics.Raycast(r, out hitInfo, MaxFollowDistance, ~playerLayer))
            backDist = Mathf.Min(hitInfo.distance - 0.1f, MaxFollowDistance);

        transform.position = (Target.position + HeightOffset * Vector3.up) - backDist * transform.forward;
    }
}
