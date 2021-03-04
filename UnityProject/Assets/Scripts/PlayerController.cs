using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(CharacterController))]
public class PlayerController : MonoBehaviour
{
    public Transform CameraTransform;
    public float MoveSpeed = 5.0f;
    public Animator Animation;

    CharacterController controller;

    Vector2 moveInput = new Vector2();
    bool jumpPressed = false;
    Vector3 velocity = new Vector3(0, 0, 0);
    Vector3 hitDirection = Vector3.zero;

    float deathTimer = 0.0f;

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
        Animation.SetFloat("Forwards", moveInput.y);
        Animation.SetBool("Jump", !controller.isGrounded);

        if (Input.GetKeyDown("g") && controller.isGrounded && moveInput.magnitude == 0.0f || deathTimer >= 60.0f)
        {
            Animation.applyRootMotion = true;
            Animation.SetBool("Gangnam Style", true);
            enabled = false;
        }

        if (moveInput.magnitude > 0.0f)
        {
            deathTimer = 0.0f;
            Vector3 camForward = CameraTransform.forward;
            camForward.y = 0;
            camForward.Normalize();

            transform.forward = camForward;
        } else
        {
            deathTimer += Time.deltaTime;
        }
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

        if (!controller.isGrounded)
            hitDirection = Vector3.zero;

        if (moveInput.magnitude == 0.0f)
        {
            Vector3 horizontalHitDirection = hitDirection;
            horizontalHitDirection.y = 0;
            float displacement = horizontalHitDirection.magnitude;
            if (displacement > 0)
                velocity -= 0.2f * horizontalHitDirection / displacement;
        }

        controller.Move(velocity * Time.fixedDeltaTime);
    }

    private void OnControllerColliderHit(ControllerColliderHit hit)
    {
        hitDirection = hit.point - transform.position;
    }
}
