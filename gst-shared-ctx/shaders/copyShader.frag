#version 100

precision mediump float;

varying vec3 ourColor;
varying vec2 TexCoord;

uniform sampler2D ourTexture;

void main() {
    //FragColor = vec4(ourColor, 1.0f);
    vec4 t = vec4(ourColor, 1.0);
//    gl_FragColor = texture2D(ourTexture, TexCoord);
    gl_FragColor = texture2D(ourTexture, TexCoord) * vec4(ourColor, 1.0);
    //gl_FragColor = vec4(ourColor, 1.0);
}
