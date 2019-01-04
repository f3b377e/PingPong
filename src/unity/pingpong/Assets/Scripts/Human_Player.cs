using UnityEngine;
using System.Collections;

public class Human_Player : MonoBehaviour {
	
	private Vector3 cp;
	private Vector3 lp;
    private CursorLockMode wantedMode;

	public float speed;

	public float lastVelocity;

	public AI_Player aiBat;

	// public Texture2D particleTexture;

	// public Transform p;

	public bool firstServe = true;

	public Vector3 firstPostion;

	public static int points;

	public bool canMoveWithMouse;

	// Use this for initialization
	void Start () {
		points = 0;
		firstPostion = transform.position;
	}
	
	// Update is called once per frame
	void Update () {
		if(canMoveWithMouse) {
			transform.eulerAngles = new Vector3 (transform.eulerAngles.x,transform.eulerAngles.y,transform.position.x*-10);

            transform.position = new Vector3(
                Mathf.Lerp(transform.position.x,transform.position.x+Input.GetAxis("Mouse X"),0.2f),
                Mathf.Lerp(transform.position.y,transform.position.y+Input.GetAxis("Mouse Y"),0.2f),
                transform.position.z);

			
			
			
			if(transform.position.x > 4)
				transform.position = new Vector3(4,transform.position.y,transform.position.z);
			if(transform.position.x < -4)
				transform.position = new Vector3(-4,transform.position.y,transform.position.z);
				
			if(transform.position.y < 1.5f)
				transform.position = new Vector3(transform.position.x,1.5f,transform.position.z);
			if(transform.position.y > 2.5)
				transform.position = new Vector3(transform.position.x,2.5f,transform.position.z);
		}
	}

	void OnCollisionEnter(Collision other)
	{
			
		if(other.collider.tag == "ball" && !firstServe)
		{
				

			cp = transform.position;
			float diff = (cp.x-lp.x);
			if(diff < -1.1f)
			{
					diff = -1.1f;
			}
			if(diff > 1.1f)
			{
					diff = 1.1f;
			}
			other.rigidbody.GetComponent<PingPong_Ball>().batStatus = "ubat";

			other.rigidbody.velocity = Vector3.zero;
			other.rigidbody.isKinematic = true;

			other.transform.position = other.contacts[0].point;
			other.transform.position += new Vector3(0,0,0.1f) ;
			other.rigidbody.isKinematic = false;
			other.rigidbody.AddForce(transform.forward*15,ForceMode.Impulse);

			other.rigidbody.AddForce(transform.right*diff*2,ForceMode.Impulse);
			if(other.transform.position.y < 1.68f)
				other.rigidbody.AddForce(Vector3.up*1.6f,ForceMode.Impulse);
			else
				other.rigidbody.AddForce(Vector3.up*1.2f,ForceMode.Impulse);

			// p.GetComponent<ParticleRenderer>().materials[0].mainTexture = particleTexture;

			AI_Player.move = true;
			aiBat.HitDirection(diff);

		}
	}

	void OnTriggerEnter(Collider other)
	{
		if(other.GetComponent<Collider>().tag == "ball")
		{
			other.transform.SendMessage("Serve",transform);
		}
	}

	public void RegisterSpin()
	{
		lp = transform.position;
	}

	public void Reset()
	{
		if(canMoveWithMouse)
			transform.position = firstPostion;
		GetComponent<Collider>().isTrigger = true;
		GetComponent<Rigidbody>().isKinematic =false;
		firstServe = true;
	}
}
