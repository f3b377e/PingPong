using System;
using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using System.Runtime.InteropServices;

public class AI_Player : MonoBehaviour
{

    public float batSpeed;
    public Transform ball;
    public float speed;
    public static bool move;
    public float hitDirection;
    public Vector3 firstPostion;
    public static int points;

    public Text textAIPosition;
    public Text textCamPosition;
    public Text texPnts;

    private int x, y, z;
    private float x1, y1, z1;
    private IntPtr pos;

    [DllImport("CppToUnity")]
    unsafe static extern void GetPos(IntPtr pos, ref int x, ref int y, ref int z);
    [DllImport("CppToUnity")]
    private static extern IntPtr InitSharePos();
    [DllImport("CppToUnity")]
    unsafe private static extern IntPtr RemoveSharePos(IntPtr pos);

    void Start()
    {
        pos = InitSharePos();
        x = 0; y = 0; z = 0;
        x1 = 0; y1 = 0; z1 = 0;
        points = 0;
        move = true;
        firstPostion = transform.position;
        textAIPosition.text = "X:0 Y:0 Z:0";
        textCamPosition.text = "X:0 Y:0 Z:0";
    }

    void PosFromCamToUnity(int x, int y, int z)
    {
        x1 = x - 358;
        x1 = (float)0.0080 * x1;
        y1 = (float)(y * 0.01016);
        z1 = (z - 368) /64;
    }

    void Update()
    {
        GetPos(pos, ref x, ref y, ref z);
        PosFromCamToUnity(x, y, z);

        transform.eulerAngles = new Vector3(transform.eulerAngles.x, transform.eulerAngles.y, transform.position.x * -10);

        if (move && transform.position.y >= 1.4f && transform.position.x > -4f && transform.position.x < 4f)
        {
            if (z1 > 0)
            {
                // se minore di 0 allora la ball si trova nella parte del campo del giocatore
                transform.position = Vector3.Lerp(transform.position,
                                                  new Vector3(0, transform.position.y, transform.position.z),
                                                  Time.deltaTime * batSpeed);
            }
            else
            {
                // si trova nella parte del campo dell IA

                //transform.position.Set(x1, ball.transform.position.y + 0.2f, transform.position.z);  
                transform.position = Vector3.Lerp(transform.position,
                                                  new Vector3(x1, y1, transform.position.z),
                                                  Time.deltaTime * batSpeed);
            }
        }
        if (transform.position.y < 1.4f)
            transform.position = new Vector3(transform.position.x, 1.4f, transform.position.z); //transform.position.y = 1.4f;
    }
    void OnCollisionEnter(Collision other)
    {
        if (other.collider.tag == "ball")
        {
            if (transform.position.x < -1.7f || transform.position.x > 1.7f)
            {
                hitDirection *= -1;
                hitDirection = hitDirection / 2;
            }
            else
            {
                if (UnityEngine.Random.Range(1, 3) == 1)
                    hitDirection = -hitDirection;
            }

            other.rigidbody.GetComponent<PingPong_Ball>().batStatus = "abat";
            speed = 15;
            other.rigidbody.velocity = Vector3.zero;
            other.rigidbody.isKinematic = true;

            other.transform.position = other.contacts[0].point;
            other.transform.position -= new Vector3(0, 0, 0.1f);
            other.rigidbody.isKinematic = false;

            if (transform.position.y < 1.55f)
            {
                other.rigidbody.AddForce(Vector3.up * 4, ForceMode.Impulse);
                other.rigidbody.AddForce(-transform.forward * speed / 1.5f, ForceMode.Impulse);

                other.rigidbody.AddForce(transform.right * hitDirection * 1.5f, ForceMode.Impulse);
            }
            else if (transform.position.y < 1.7f)
            {
                other.rigidbody.AddForce(Vector3.up * 2, ForceMode.Impulse);
                other.rigidbody.AddForce(-transform.forward * speed, ForceMode.Impulse);

                other.rigidbody.AddForce(transform.right * hitDirection * 2, ForceMode.Impulse);
            }
            else
            {
                other.rigidbody.AddForce(Vector3.up * 1.5f, ForceMode.Impulse);
                other.rigidbody.AddForce(-transform.forward * speed, ForceMode.Impulse);

                other.rigidbody.AddForce(transform.right * hitDirection * 2, ForceMode.Impulse);
            }

            // p.GetComponent<ParticleRenderer>().materials[0].mainTexture = particleTexture;
            move = false;
        }
    }
    public void HitDirection(float x)
    {
        hitDirection = x;
    }
    public void Reset()
    {
        transform.position = firstPostion;
        move = true;
    }
    private void OnApplicationQuit()
    {
        /* Sent to all game objects before the application quits    .
         * In the editor this is called when the user stops playmode. */
        RemoveSharePos(pos);
    }
    private void LateUpdate(){
        if (Time.frameCount % 20 == 0)
            UpdateText();
    }
    private void UpdateText()
    {
        textAIPosition.text = "bat X:"+x1+" Y:"+y1+" Z:"+z1;
        textCamPosition.text = "ball X:" + x + " Y:" + y + " Z:" + z;
        //texPnts.text = "AI     Pnts :" + points.ToString();
    }
}
