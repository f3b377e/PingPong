using UnityEngine;
using System.Collections;

public class Table_Net : MonoBehaviour {

    private bool getCollision = true;

    void OnTriggerEnter(Collider other)
    {
            if(other.GetComponent<Collider>().tag == "ball")
            {
                    if(other.GetComponent<Rigidbody>().GetComponent<PingPong_Ball>().batStatus == "abat" && getCollision)
                    {
                            getCollision = false;
                            other.GetComponent<Rigidbody>().velocity = Vector3.zero;
                            other.GetComponent<Rigidbody>().AddForce(transform.forward*5,ForceMode.Impulse);
                            StartCoroutine(ResetThings(other.transform));
                            Human_Player.points++;
                            // Camera_Follow.userPoints = Human_Player.points.ToString();
                    }
                    if(other.GetComponent<Rigidbody>().GetComponent<PingPong_Ball>().batStatus == "ubat" && getCollision)
                    {
                            getCollision = false;
                            other.GetComponent<Rigidbody>().velocity = Vector3.zero;
                            other.GetComponent<Rigidbody>().AddForce(-transform.forward*5,ForceMode.Impulse);
                            StartCoroutine(ResetThings(other.transform));
                            AI_Player.points++;
                            // Camera_Follow.aiPoints = AI_Player.points.ToString();
                    }
            }
    }

    IEnumerator ResetThings(Transform other)
    {
        yield return new WaitForSeconds(1);
        other.GetComponent<Rigidbody>().GetComponent<PingPong_Ball>().Reset();
        getCollision = true;
    }
}
