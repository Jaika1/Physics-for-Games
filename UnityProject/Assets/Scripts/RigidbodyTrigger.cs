using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RigidbodyTrigger : MonoBehaviour
{
    public float ExplosiveForce = 0.0f;

    private void OnTriggerEnter(Collider other)
    {
        RagdollScript ragdoll = other.GetComponent<RagdollScript>();
        if (!ragdoll) return;

        ragdoll.EnableRagdoll(ExplosiveForce);
    }
}
