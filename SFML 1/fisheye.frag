uniform sampler2D texture;
uniform vec2 resolution;  // Resolution of the view
uniform float strength;    // Strength of the fisheye effect

void main() {
    vec2 uv = gl_FragCoord.xy / resolution;  // Normalized coordinates [0,1]
    vec2 center = vec2(0.5, 0.5);            // Center of the screen

    vec2 offset = uv - center;               // Offset from center
    float dist = length(offset);             // Distance from center

    // Fisheye distortion
    float factor = 1.0 + strength * (1.0 - pow(dist, 2.0));
    vec2 distortedUV = offset * factor + center;

    // Sample the texture with distorted coordinates
    if (distortedUV.x < 0.0 || distortedUV.x > 1.0 || distortedUV.y < 0.0 || distortedUV.y > 1.0) {
        gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0); // Black for out-of-bounds
    } else {
        gl_FragColor = texture2D(texture, distortedUV);
    }
}
