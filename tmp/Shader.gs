layout (lines) in;
layout (line_strip, max_vertices = 2) out;

layout(std430,binding = 5) readonly buffer SSBO {
  unsigned int data[];
} gSSBO;


void main(void){
unsigned int = gSSBO.data[0];
	//if(gSSBO.data[0] == 1){
	gl_Position = gl_in[0].gl_Position; 
    EmitVertex();

	gl_Position = gl_in[1].gl_Position; 
    EmitVertex();
    EndPrimitive();
	//}
}