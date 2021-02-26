using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Rigidbody))]
public class Cannonball : MonoBehaviour
{
    public float Speed = 20;

    Rigidbody rBody;

    // Start is called before the first frame update
    void Start()
    {
        rBody = GetComponent<Rigidbody>();
        rBody.isKinematic = true;
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        if (Input.GetKey(KeyCode.Space))
        {
            if (rBody.isKinematic)
            {
                rBody.isKinematic = false;
                rBody.AddForce(transform.forward * Speed, ForceMode.VelocityChange);
            }
            else
                rBody.AddForce(rBody.velocity.normalized * Speed, ForceMode.VelocityChange);
        }
    }
}
