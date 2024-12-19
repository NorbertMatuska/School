#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

const float gzry = 9.80665;
const float Splo = 0.03; //plocha
const float Codp = 0.6; //odpor vzduchu
const float ro = 1.3; //hustota vzduchu?
const float hmot = 10.0; //hmotnost

float k0, vterm; //analyt. fun
float z0, v0;

void Euler(const float v0,const float z0, const float dt);
void analyt(const float v0, const float z0, const float dt);

int main(int argc, char **argv) {
	const float dt = 0.01;
	//skopiruj nejake zadavanie s prikazoveho riadka
	//z0, v0
	scanf(" %f", &z0);
	scanf(" %f", &v0);
	
	if(z0 < 0 || v0 < 0) {
		printf("iba kladne hodnoty\n");
		exit(0);
	}
	
	k0 = 0.5*Codp * Splo * ro / hmot;
	vterm = sqrt(2.0*hmot*gzry/(ro*Codp*Splo));
	printf("vterm = %.3f m/s \n", vterm);
	//vykonat funkciu
	Euler(v0,z0,dt);
	analyt(v0,z0,dt); 
	//analyt je na du
	//do suboru t_vz_zsur_anat.dat zapiseme do stlpcov cas, vz, zsur
	//vz = -vterm*tanh(gzry*cas/vterm);
	//z treba tiez vycislit
	
	return 0;
}

float funv(const float cas, const float vz, const float zsur){
	return -gzry-k0*fabs(vz)*vz; //fabs = absoulutna hodnota
}

float funz(const float cas, const float vz, const float zsur){
	return vz;
}

float funv_analytic(const float t){
	return -vterm*tanh(-gzry*t/vterm);
}

float funz_analytic(const float t){
	return z0-((vterm*vterm)/(-gzry))*log(cosh(-gzry*t/vterm));
}

void Euler(const float v0, const float z0, const float dt) {
	FILE *f;
	float cas = 0.0;
	float vz = v0;
	float zsur = z0;
	f = fopen("t_vz_zsur_EM.dat","w");
	fprintf(f, "%f, %f, %f\n",cas,vz,zsur);

	while(zsur > 0.0){

		vz += dt*funv(cas,vz,zsur);
		zsur += dt*funz(cas,vz,zsur);
		cas += dt;
		fprintf(f,"%f %f %f", cas,vz,zsur);
	}
	fclose(f);
	printf("Euler cas dopadu = %f\n",cas);
}

void analyt (float v0, float z0, float dt) {
	FILE *fw;
	float cas = 0.0;
	float vz = -vterm * tanh(gzry*cas/vterm);
	float zsur = z0;
	printf("bruh1\n");
	fw = fopen("t_vz_zsur_ANALYTIC.dat", "w");
	if(fw == NULL) return;
	fprintf(fw, "%f %f %f\n", cas, vz, zsur); //cas 0
	//printf("bruh2\n");
	
	while(zsur > 0.0) {
		vz = -vterm*tanh(gzry*cas/vterm);
		zsur = z0-((vterm*vterm)/(-gzry))*log(cosh(gzry*cas/vterm));
		cas += dt;
		printf("%f %f %f\n", cas, vz, zsur);
		//fprintf(fw, "%f %f %f\n", cas, vz, zsur);
		printf("while\n");
	}
	fclose(fw);
	printf("Analyt cas dopadu: %f\n", cas);
	
}