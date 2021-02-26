using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Rigidbody))]
public class SleepVisualizer : MonoBehaviour
{
    public Material AwakeMaterial;
    public Material SleepMaterial;

    Rigidbody rBody;
    bool wasSleeping;

    // Start is called before the first frame update
    void Start()
    {
        rBody = GetComponent<Rigidbody>();
        wasSleeping = !rBody.IsSleeping();
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        if (rBody.IsSleeping() && !wasSleeping && SleepMaterial != null)
        {
            wasSleeping = true;
            GetComponent<MeshRenderer>().material = SleepMaterial;
        }
        
        if (!rBody.IsSleeping() && wasSleeping && AwakeMaterial != null)
        {
            wasSleeping = false;
            GetComponent<MeshRenderer>().material = AwakeMaterial;
        }
    }
}
