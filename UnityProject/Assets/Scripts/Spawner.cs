using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Spawner : MonoBehaviour
{
    public GameObject Prefab;
    public float Delay = 0.1f;
    float delayElapsed = 0.0f;

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKey(KeyCode.Space) && delayElapsed <= 0.0f)
        {
            var n = Instantiate(Prefab);
            n.transform.position = transform.position;
            n.GetComponent<Rigidbody>().AddForce(new Vector3(Random.Range(-1.0f, 1.0f), Random.Range(-1.0f, 1.0f), Random.Range(-1.0f, 1.0f)) * 100.0f, ForceMode.VelocityChange);
            delayElapsed = Delay;
        }

        if (delayElapsed > 0) delayElapsed -= Time.deltaTime;
    }
}
