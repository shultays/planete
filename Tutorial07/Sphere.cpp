
//x y z
void init_static(){
	Quaternion q;

	qs[0][0][0] = Quaternion::CreateFromAxisAngle(Vector3(0, 0, 1), PI_2);
	qs[1][0][0] = Quaternion::CreateFromAxisAngle(Vector3(0, 0, 1), PI_2);
	qs[1][1][0] = Quaternion::CreateFromAxisAngle(Vector3(0, 0, 1), PI);
	qs[0][1][0] = Quaternion::CreateFromAxisAngle(Vector3(0, 0, 1), PI3_2);


	qs[0][0][1] = Quaternion::CreateFromAxisAngle(Vector3(1, 0, 0), PI2)*Quaternion::CreateFromAxisAngle(Vector3(0, 0, 1), PI3_2);
	qs[1][0][1] = Quaternion::CreateFromAxisAngle(Vector3(1, 0, 0), PI2);
	qs[1][1][1] = Quaternion::CreateFromAxisAngle(Vector3(1, 0, 0), PI2)*Quaternion::CreateFromAxisAngle(Vector3(0, 0, 1), PI_2);
	qs[0][1][1] = Quaternion::CreateFromAxisAngle(Vector3(1, 0, 0), PI2)*Quaternion::CreateFromAxisAngle(Vector3(0, 0, 1), PI);

}

Vector3 fix(Vector3 &v){
	return v*qs[v.x < 0][v.y < 0][v.z < 0];
}