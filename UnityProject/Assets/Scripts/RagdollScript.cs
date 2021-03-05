using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Rendering.PostProcessing;

public class RagdollScript : MonoBehaviour
{
    public Animator ModelAnimator;
    public OrbitalCamera MainCamera;
    public Transform RagdollTarget;
    public PostProcessVolume RagdollVolume;
    Rigidbody[] ragdollBodies;

    private void Start()
    {
        ragdollBodies = ModelAnimator.GetComponentsInChildren<Rigidbody>(true);
    }

    public void EnableRagdoll(Vector3 midpoint, float? explosiveForce)
    {
        ModelAnimator.enabled = false;
        Array.ForEach(ragdollBodies, r => r.isKinematic = false);
        ModelAnimator.transform.SetParent(null);

        if (MainCamera && RagdollTarget)
        {
            MainCamera.Target = RagdollTarget;
            MainCamera.HeightOffset = 0;
        }
        if (RagdollVolume) RagdollVolume.enabled = true;

        if (explosiveForce.HasValue)
        {
            foreach (Rigidbody r in ragdollBodies)
            {
                r.AddExplosionForce(explosiveForce.Value, midpoint, 50.0f, 0.0f, ForceMode.VelocityChange);
            }
        }

        gameObject.SetActive(false);
    }

    public void EnableRagdoll() => EnableRagdoll(Vector3.zero, 0.0f);

    public void EnableRagdoll(float explosiveForce) => EnableRagdoll(transform.position, explosiveForce);
}
