package com.jp.contenedor;

import static android.os.SystemClock.sleep;
import static android.provider.ContactsContract.CommonDataKinds.Website.URL;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.view.animation.Animation;
import android.view.animation.RotateAnimation;
import android.widget.ImageView;
import android.widget.TextView;

import com.android.volley.Cache;
import com.android.volley.Network;
import com.android.volley.Request;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.BasicNetwork;
import com.android.volley.toolbox.DiskBasedCache;
import com.android.volley.toolbox.HurlStack;
import com.android.volley.toolbox.StringRequest;
import com.android.volley.toolbox.Volley;


import java.io.BufferedInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;

public class MainActivity<RequestQueue, stringRequest> extends AppCompatActivity {
    ImageView imagen;
    TextView cuadroTexto;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ///
        imagen = (ImageView) findViewById(R.id.imagen_centro);
        cuadroTexto=(TextView) findViewById(R.id.texto_estado);
        imagen.setImageResource(R.drawable.carga);
        rotarImagen(imagen);
        // Instantiate the RequestQueue.
        RequestQueue queue = (RequestQueue) Volley.newRequestQueue(this);
        String url ="https://script.google.com/macros/s/AKfycbyiSEiFdjeuqYmRroEhbCGyaqrOg70VnzrgyDD4zfLmoodFK_Gvcxv7au6EV1YYjcQuZA/exec";

        // Request a string response from the provided URL.
        StringRequest stringRequest = new StringRequest(Request.Method.GET, url,
                new Response.Listener<String>() {
                    @Override
                    public void onResponse(String response) {
                        // Display the first 500 characters of the response string.
                        if(response.equals("Vacío")){
                            cuadroTexto.setText("CONTENEDOR VACÍO");
                            imagen.setImageResource(R.drawable.vacio);
                            imagen.clearAnimation();
                        }
                        else if(response.equals("Lleno")) {
                            cuadroTexto.setText("CONTENEDOR LLENO");
                            imagen.setImageResource(R.drawable.lleno);
                            imagen.clearAnimation();
                        }else{
                            imagen.setScaleX(0.5F);
                            imagen.setScaleY(0.5F);
                            rotarImagen(imagen);
                        }
                    }
                }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                cuadroTexto.setText("Estado: Error");
            }
        });

        // Add the request to the RequestQueue.
        ((com.android.volley.RequestQueue) queue).add(stringRequest);
    }
    private void rotarImagen(View view){
        RotateAnimation animation = new RotateAnimation(0, 360,
                RotateAnimation.RELATIVE_TO_SELF, 0.5f,
                RotateAnimation.RELATIVE_TO_SELF, 0.5f);

        animation.setDuration(2000);
        animation.setRepeatCount(Animation.INFINITE);
        animation.setRepeatMode(Animation.REVERSE);
        view.startAnimation(animation);
    }

}