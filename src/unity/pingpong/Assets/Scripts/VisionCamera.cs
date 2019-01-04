using System;
using UnityEngine;
using System.Threading;
using System.Collections;
using System.Runtime.InteropServices;

using stopwatch = System.Diagnostics.Stopwatch;


public class VisionCamera : MonoBehaviour
{
    public bool isTopCam;
    private char poscam;

    private Camera cam;
    private RenderTexture renderTexture;
    private Texture2D image;
    private Rect rect;
    private IntPtr strptr;
    private Thread _t;
    public bool isthreadrunnig;
    private ushort fmod;

    [DllImport("CppToUnity")]
    private static extern void SetTextureCVMat(IntPtr img, IntPtr texData);
    [DllImport("CppToUnity")]
    private static extern IntPtr InitSharedRegion(int width, int heigth, int channel, bool istopcam);
    [DllImport("CppToUnity")]
    private static extern void RemoveSharedRegion(IntPtr img);

    unsafe void TextureToCVMat(IntPtr structptr, Texture2D texData)
    {
        Color32[] texDataColor = texData.GetPixels32();
        //Pin Memory
        fixed (Color32* p = texDataColor)
        {
            SetTextureCVMat(structptr, (IntPtr)p);
        }
    }
    private void Awake() /* Awake(): this is the first function called by unity*/
    {
        cam = gameObject.GetComponent<Camera>();
        renderTexture = cam.targetTexture;
        poscam = (isTopCam) ? 'T' : 'F';
        fmod = (ushort)((isTopCam) ? 0 : 1);
        image = new Texture2D(renderTexture.width, renderTexture.height, TextureFormat.RGB24, false);
        rect = new Rect(0, 0, renderTexture.width, renderTexture.height);
        
        strptr = InitSharedRegion(image.width, image.height, 4, isTopCam);
    }
    void Start() /* Start(): after awake() and before update() */
    {
        // Application doesn't pauses when it is in the background
        Application.runInBackground = true;
        if (isTopCam){
            _t = new Thread(Garbage);
            _t.Start();
        }
        // InvokeRepeating("CamUpdate", 1, 1/60);
    }
    void CamUpdate()
    {
        //StartCoroutine(MyUpdate(strptr, image));
    }
    void Garbage()
    {
        isthreadrunnig = true;
        while (isthreadrunnig){
            Thread.Sleep(35);
            System.GC.Collect();
        }
    }
    IEnumerator MyUpdate(IntPtr ptr, Texture2D texture)
    {
        yield return new WaitForEndOfFrame();
        RenderTexture.active = renderTexture;
        image.ReadPixels(rect, 0, 0);
        RenderTexture.active = null;
        TextureToCVMat(ptr, texture);
    }

    void Update() // called every frame
    {
        if (Time.frameCount % 2 == fmod)
            StartCoroutine(MyUpdate(strptr, image));
    }
    private void OnApplicationQuit()
    {
        /* Sent to all game objects before the application quits.
         * In the editor this is called when the user stops playmode. */
        if(isTopCam){
            isthreadrunnig = false;
            _t.Abort();
        }
        RemoveSharedRegion(strptr);
    }
    void SaveImage(string filename, byte[] img)
    {
        filename = Application.dataPath + "/Screenshot/" + filename;
        System.IO.File.WriteAllBytes(filename, img);
    }
    private void OnPostRender(){
        if (Input.GetKeyDown(KeyCode.F11))
        {
            SaveImage(poscam + "camScreenshot.png", image.EncodeToPNG());
            Debug.Log("Screenshot saved in Screenshot/" + poscam + "camScreenshot.png");
        }
        if (Input.GetKeyDown(KeyCode.T))
        {
            Debug.Log(poscam + "CAM " + image.dimension);
        }
    }
}