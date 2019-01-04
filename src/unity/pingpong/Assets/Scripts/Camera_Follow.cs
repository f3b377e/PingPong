using UnityEngine;
using System.Collections;
using UnityEngine.SceneManagement;

public class Camera_Follow : MonoBehaviour {

	public float speed;
	public Transform bat;

	public static string userPoints ;
	public static string aiPoints ;

	void Start()
	{
		userPoints = "0";
		aiPoints = "0";
	}

	void Update () {
		//if(bat && bat.transform.position.x > -3 && bat.transform.position.x < 3)
			//transform.position = Vector3.Lerp(transform.position,new Vector3(bat.transform.position.x,transform.position.y,transform.position.z),Time.deltaTime*speed);
		if(Input.GetKeyDown(KeyCode.R))
		{
			SceneManager.LoadScene("TableTennis", LoadSceneMode.Single);
		}
	}
}
