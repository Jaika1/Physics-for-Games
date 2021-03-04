using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Rigidbody))]
public class Spring : MonoBehaviour
{
    public float SpringForce = 10.0f;
    Rigidbody rbody;

    private void Start()
    {
        rbody = GetComponent<Rigidbody>();
    }

    private void OnTriggerEnter(Collider other)
    {
        RagdollScript ragdoll = other.GetComponent<RagdollScript>();
        if (!ragdoll) return;

        ragdoll.EnableRagdoll();
        rbody.isKinematic = false;
        rbody.AddForce(Vector3.up * SpringForce, ForceMode.VelocityChange);
    }
}
