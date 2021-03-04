using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RemoveParentOnBreak : MonoBehaviour
{
    ParticleSystem particles;

    private void Start()
    {
        particles = GetComponent<ParticleSystem>();
    }

    private void OnJointBreak(float breakForce)
    {
        transform.SetParent(null);
        transform.DetachChildren();
        particles.Play();
    }
}
