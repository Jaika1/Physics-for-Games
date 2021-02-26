using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(CharacterController))]
public class PlayerController : MonoBehaviour
{
    public Transform CameraTransform;
    public float MoveSpeed = 5.0f;

    CharacterController controller;

    Vector2 moveInput = new Vector2();
    bool jumpPressed = false;
    Vector3 velocity = new Vector3(0, 0, 0);

    void Awake()
    {
        controller = GetComponent<CharacterController>();
    }

    // Update is called once per frame
    private void Update()
    {
        moveInput.x = Input.GetAxis("Horizontal");
        moveInput.y = Input.GetAxis("Vertical");
        jumpPressed = Input.GetButton("Jump");
    }

    void FixedUpdate()
    {
        Vector3 camForward = CameraTransform.forward;
        camForward.y = 0;
        camForward.Normalize();

        Vector3 delta = (moveInput.x * CameraTransform.right + moveInput.y * camForward) * MoveSpeed;

        if (controller.isGrounded || moveInput.magnitude > 0.0f)
        {
            velocity.x = delta.x;
            velocity.z = delta.z;
        }

        if (controller.isGrounded)
        {
            if (velocity.y < 0) velocity.y = 0;

            if (jumpPressed)
                velocity.y = 10.0f;
        }

        velocity += Physics.gravity * Time.fixedDeltaTime;

        controller.Move(velocity * Time.fixedDeltaTime);
    }
}
