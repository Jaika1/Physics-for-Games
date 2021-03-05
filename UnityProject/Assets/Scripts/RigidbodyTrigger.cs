using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RigidbodyTrigger : MonoBehaviour
{
    private void OnTriggerEnter(Collider other)
    {
        RagdollScript ragdoll = other.GetComponent<RagdollScript>();
        if (!ragdoll) return;

        ragdoll.EnableRagdoll(transform.position, GetComponent<Rigidbody>()?.velocity.magnitude);
    }
}
