using UnityEngine;
using System.Collections;

public class PingPong_Ball : MonoBehaviour {

	public int factor;

	public bool reset = false;

	public Human_Player userBatScript;
	public AI_Player aiBatScript;

	public string batStatus;

	private float speed = 12;
	private Vector3 firstpostion;
	private bool firstServe;
	private Transform batTransform;
	private int groundCount;
	private string tableSideName;

	void Start () {
		firstpostion = transform.position;
	}

	public void Reset()
	{
		reset = false;

		GetComponent<Rigidbody>().useGravity = false;
		GetComponent<Rigidbody>().velocity = Vector3.zero;
		transform.position = firstpostion;
		aiBatScript.Reset();
		userBatScript.Reset();

	}
	
	
	public void Serve(Transform t)
	{
		if(Random.Range(1,3) == 1)
		{
			factor = -1;
		}
		else
		{
			factor = 1;
		}
		reset = true;

		GetComponent<Rigidbody>().useGravity = true;
		GetComponent<Rigidbody>().AddForce(Vector3.down*2.7f,ForceMode.Impulse);
		GetComponent<Rigidbody>().AddForce(transform.forward*speed,ForceMode.Impulse);

		if(Random.Range(1,3) == 1)
			GetComponent<Rigidbody>().AddForce(transform.right*0.4f*2,ForceMode.Impulse);
		else
			GetComponent<Rigidbody>().AddForce(transform.right*-0.4f*2,ForceMode.Impulse);

		firstServe = true;
		batTransform = t;
	}

	void OnCollisionEnter(Collision collisionInfo) {

		if(collisionInfo.collider.name == "UserSideTable")
		{
				userBatScript.RegisterSpin();
				tableSideName = "UserSideTable";
		}

		if(collisionInfo.collider.name == "AiSideTable")
		{
			if(firstServe)
			{
				batTransform.GetComponent<Collider>().isTrigger = false;
				batTransform.GetComponent<Rigidbody>().isKinematic =true;
				batTransform.GetComponent<Human_Player>().firstServe = false;
				firstServe = false;
			}

			tableSideName = "AiSideTable";
		}

		if(collisionInfo.collider.name == "Wall")
		{
			groundCount++;
			if(groundCount == 2)
			{
				Reset();
				groundCount = 0;

				if(batStatus == "abat")
				{
					if(tableSideName == "UserSideTable"){
							AI_Player.points++;
							//CameraFollow.aiPoints = AiBat.points.ToString();
					}
					if(tableSideName == "AiSideTable"){
							Human_Player.points++;
							//CameraFollow.userPoints = UserBat.points.ToString();
					}
				}

				if(batStatus == "ubat")
				{
					if(tableSideName == "AiSideTable"){
							Human_Player.points++;
							//CameraFollow.userPoints = UserBat.points.ToString();
					}
					if(tableSideName == "UserSideTable"){
							Human_Player.points++;
							//CameraFollow.aiPoints = AiBat.points.ToString();
					}
				}
			}
		}
	}
}
