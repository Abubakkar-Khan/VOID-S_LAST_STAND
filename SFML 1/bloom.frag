// bloom.frag
uniform float time;
uniform vec2 resolution;
uniform sampler2D texture;

void main() {
    vec2 uv = gl_FragCoord.xy / resolution.xy;
    
    // Get the texture color at the current pixel
    vec4 color = texture2D(texture, uv);
    
    // Create a glowing effect by modifying the alpha and color intensity
    float glowIntensity = 0.5 + 0.5 * sin(time * 5.0);
    color.rgb *= glowIntensity;
    color.a = 1.0;  // Ensure alpha remains opaque

    // Final output
    gl_FragColor = color;
}
