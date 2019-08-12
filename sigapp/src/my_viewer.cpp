
# include "my_viewer.h"

# include <sigogl/ui_button.h>
# include <sigogl/ui_radio_button.h>
# include <sig/sn_primitive.h>
# include <sig/sn_transform.h>
# include <sig/sn_manipulator.h>
# include <sigogl/ws_run.h>
GsMat tran;
float pi = 3.14f;
float xcam=0;
float zcam=0;
int lmid_count = 0;
int lhand_count = 0;
int rmid_count = 0;
int rhand_count = 0;
int lfoot_count = 0;
int rfoot_count = 0;
int lleg_count = 0;
int rleg_count = 0;

MyViewer::MyViewer ( int x, int y, int w, int h, const char* l ) : WsViewer(x,y,w,h,l)
{
	_nbut=0;
	_animating=false;
	build_ui ();
	build_scene ();
	cmd(WsViewer::VCmdAsIs);
}
void MyViewer::new_shadow(int index, int inc)
{
	if (index == -1) { //default light source
		light[0] = 0;
		light[1] = 1;
		light[2] = 1;
	}
	else {
		this->light[index] += float(0.1*inc);
	}

	float  dot;
	float shadow[16];

	dot = ground[0] * light[0] +
		ground[1] * light[1] +
		ground[2] * light[2] +
		ground[3] * light[3];

	shadow[0] = dot - light[0] * ground[0];
	shadow[1] = 0.0f - light[0] * ground[1];
	shadow[2] = 0.0f - light[0] * ground[2];
	shadow[3] = 0.0f - light[0] * ground[3];

	shadow[4] = 0.0f - light[1] * ground[0];
	shadow[5] = dot - light[1] * ground[1];
	shadow[6] = 0.0f - light[1] * ground[2];
	shadow[7] = 0.0f - light[1] * ground[3];

	shadow[8] = 0.0f - light[2] * ground[0];
	shadow[9] = 0.0f - light[2] * ground[1];
	shadow[10] = dot - light[2] * ground[2];
	shadow[11] = 0.0f - light[2] * ground[3];

	shadow[12] = 0.0f - light[3] * ground[0];
	shadow[13] = 0.0f - light[3] * ground[1];
	shadow[14] = 0.0f - light[3] * ground[2];
	shadow[15] = dot - light[3] * ground[3];
	//shadowMat.set(shadow);

}
void MyViewer::global(int num, int o) {

	if (num == 12&&o==1) {
		for (int ind = 0; ind <= 11; ind++) {
			SnManipulator* manip12 = e->get<SnManipulator>(ind); // access one of the manipulators
			tran.translation(xinc, 0, zinc+.1f);
			manip12->initial_mat(tran*manip12->mat());
		}
		for (int ind = 0; ind <= 11; ind++) {
			SnManipulator* manip12 = sh->get<SnManipulator>(ind); // access one of the manipulators
			tran.translation(xinc, 0, zinc + .1f);
			manip12->initial_mat(tran*manip12->mat());
		}
	}
	if (num == 12 && o == -1) {
		for (int ind = 0; ind <= 11; ind++) {
			SnManipulator* manip12 = e->get<SnManipulator>(ind); // access one of the manipulators
			tran.translation(xinc, 0, zinc-.1f);
			manip12->initial_mat(tran*manip12->mat());
		}
		for (int ind = 0; ind <= 11; ind++) {
			SnManipulator* manip12 = sh->get<SnManipulator>(ind); // access one of the manipulators
			tran.translation(xinc, 0, zinc - .1f);
			manip12->initial_mat(tran*manip12->mat());
		}
	}
	if (num == 13&&o==1) {
		for (int ind = 0; ind <= 11; ind++) {
			SnManipulator* manip12 = e->get<SnManipulator>(ind); // access one of the manipulators
			tran.translation(xinc+.1f, 0, zinc);
			manip12->initial_mat(tran*manip12->mat());
		}
		for (int ind = 0; ind <= 11; ind++) {
			SnManipulator* manip12 = sh->get<SnManipulator>(ind); // access one of the manipulators
			tran.translation(xinc + .1f, 0, zinc);
			manip12->initial_mat(tran*manip12->mat());
		}
	}
	if (num == 13 && o == -1) {
		for (int ind = 0; ind <= 11; ind++) {
			SnManipulator* manip12 = e->get<SnManipulator>(ind); // access one of the manipulators
			tran.translation(xinc-.1f, 0, zinc);
			manip12->initial_mat(tran*manip12->mat());
		}
		for (int ind = 0; ind <= 11; ind++) {
			SnManipulator* manip12 = sh->get<SnManipulator>(ind); // access one of the manipulators
			tran.translation(xinc - .1f, 0, zinc);
			manip12->initial_mat(tran*manip12->mat());
		}
	}
}
void MyViewer::rotate(int num, int o) {
	SnManipulator* manip = e->get<SnManipulator>(2); // access one of the manipulators
	SnManipulator* manip2 = e->get<SnManipulator>(3); // access one of the manipulators
	SnManipulator* manip3 = e->get<SnManipulator>(4); // access one of the manipulators
	SnManipulator* manip4 = e->get<SnManipulator>(5); // access one of the manipulators
	SnManipulator* manip5 = e->get<SnManipulator>(6); // access one of the manipulators
	SnManipulator* manip6 = e->get<SnManipulator>(7); // access one of the manipulators
	SnManipulator* manip7 = e->get<SnManipulator>(8); // access one of the manipulators
	SnManipulator* manip8 = e->get<SnManipulator>(9); // access one of the manipulators
	SnManipulator* manip9 = e->get<SnManipulator>(10); // access one of the manipulators
	SnManipulator* manip10 = e->get<SnManipulator>(11); // access one of the manipulators
	SnManipulator* manip11 = e->get<SnManipulator>(0); // access one of the manipulators
	//shadow manips
	SnManipulator* manips = sh->get<SnManipulator>(2); // access one of the manipulators
	SnManipulator* manip2s = sh->get<SnManipulator>(3); // access one of the manipulators
	SnManipulator* manip3s = sh->get<SnManipulator>(4); // access one of the manipulators
	SnManipulator* manip4s = sh->get<SnManipulator>(5); // access one of the manipulators
	SnManipulator* manip5s = sh->get<SnManipulator>(6); // access one of the manipulators
	SnManipulator* manip6s = sh->get<SnManipulator>(7); // access one of the manipulators
	SnManipulator* manip7s = sh->get<SnManipulator>(8); // access one of the manipulators
	SnManipulator* manip8s = sh->get<SnManipulator>(9); // access one of the manipulators
	SnManipulator* manip9s = sh->get<SnManipulator>(10); // access one of the manipulators
	SnManipulator* manip10s = sh->get<SnManipulator>(11); // access one of the manipulators
	SnManipulator* manip11s = sh->get<SnManipulator>(0); // access one of the manipulators
	GsMat rotate;
	rotate.rotx(-pi / 72 * o);
	lmid_rot.rotx((-pi / 72)*lmid_count);
	lh_rot.rotx((-pi / 72)*lhand_count);
	rmid_rot.rotx((-pi / 72)*rmid_count);
	rh_rot.rotx((-pi / 72)*rhand_count);
	lfoot_rot.rotx((-pi / 72)*lfoot_count);
	rfoot_rot.rotx((-pi / 72)*rfoot_count);
	lleg_rot.rotx((-pi / 72)*lleg_count);
	rleg_rot.rotx((-pi / 72)*rleg_count);
	
	if (num == 3) {


		manip->initial_mat((manip->mat()*rotate));
		manip2->initial_mat(manip->mat()*lmid*lmid_rot);
		manip3->initial_mat((manip2->mat()*lhand*lh_rot));

		manips->initial_mat((shadowMat*manip->mat()*rotate));
		manip2s->initial_mat(shadowMat*manip->mat()*lmid*lmid_rot);
		manip3s->initial_mat((shadowMat*manip2->mat()*lhand*lh_rot));
		

	}
	if (num == 2) {

		manip2->initial_mat((manip2->mat()*rotate));
		manip3->initial_mat(manip2->mat()*lhand*lh_rot);
		lmid_count += 1 * o;

		manip2s->initial_mat((shadowMat*manip2->mat()*rotate));
		manip3s->initial_mat(shadowMat*manip2->mat()*lhand*lh_rot);
	}
	if (num == 1) {

		manip3->initial_mat((manip3->mat()*rotate));
		lhand_count += 1 * o;
		manip3s->initial_mat((manip3s->mat()*rotate));
	}
	if (num == 6) {


		manip4->initial_mat((manip4->mat()*rotate));
		manip5->initial_mat(manip4->mat()*rmid*rmid_rot);
		manip6->initial_mat((manip5->mat()*rhand*rh_rot));

		manip4s->initial_mat((shadowMat*manip4->mat()*rotate));
		manip5s->initial_mat(shadowMat*manip4->mat()*rmid*rmid_rot);
		manip6s->initial_mat((shadowMat*manip5->mat()*rhand*rh_rot));


	}
	if (num == 5) {


		manip5->initial_mat((manip5->mat()*rotate));
		manip6->initial_mat(manip5->mat()*rhand*rh_rot);
		manip5s->initial_mat((shadowMat*manip5->mat()*rotate));
		manip6s->initial_mat(shadowMat*manip5->mat()*rhand*rh_rot);
		rmid_count += 1 * o;
	}
	if (num == 4) {

		manip6->initial_mat((manip6->mat()*rotate));
		manip6s->initial_mat((manip6s->mat()*rotate));
		rhand_count += 1 * o;


	}
	if (num == 8) {


		manip7->initial_mat((manip7->mat()*rotate));
		manip8->initial_mat(manip7->mat()*rfoot*rfoot_rot);

		manip7s->initial_mat((shadowMat*manip7->mat()*rotate));
		manip8s->initial_mat(shadowMat*manip7->mat()*rfoot*rfoot_rot);
		rleg_count += 1 * o;


	}
	if (num == 7) {


		manip8->initial_mat((manip8->mat()*rotate));
		manip8s->initial_mat((shadowMat*manip8->mat()*rotate));
		rfoot_count += 1 * o;
	}

	if (num == 10) {


		manip9->initial_mat((manip9->mat()*rotate));
		manip10->initial_mat(manip9->mat()*lfoot*lfoot_rot);

		manip9s->initial_mat((shadowMat*manip9->mat()*rotate));
		manip10s->initial_mat(shadowMat*manip9->mat()*lfoot*lfoot_rot);
		lleg_count += 1 * o;


	}
	if (num == 9) {


		manip10->initial_mat((manip10->mat()*rotate));
		manip10s->initial_mat((shadowMat*manip10->mat()*rotate));

		lfoot_count += 1 * o;
	}
	if (num == 11) {

		head_rot.roty(-pi / 72*o);
		manip11->initial_mat((manip11->mat()*head_rot));
		manip11s->initial_mat((shadowMat*manip11->mat()*head_rot));

	}	

	if (lmid_count == 144) {
		lmid_count = 0;

	}
	if (lmid_count == 0) {
		lmid_count = 144;
	}
	if (lhand_count == 144) {
		lhand_count = 0;

	}
	if (lhand_count == 0) {
		lhand_count = 144;
	}
	//for right arm

	if (rmid_count == 144) {
		rmid_count = 0;

	}
	if (rmid_count == 0) {
		rmid_count = 144;
	}
	if (rhand_count == 144) {
		rhand_count = 0;

	}
	if (rhand_count == 0) {
		rhand_count = 144;
	}
	//right leg

	if (rfoot_count == 144) {
		rfoot_count = 0;

	}
	if (rfoot_count == 0) {
		rfoot_count = 144;
	}
	if (rleg_count == 144) {
		rleg_count = 0;

	}
	if (rleg_count == 0) {
		rleg_count = 144;
	}
	//left leg

	if (lfoot_count == 144) {
		lfoot_count = 0;

	}
	if (lfoot_count == 0) {
		lfoot_count = 144;
	}
	if (lleg_count == 144) {
		lleg_count = 0;

	}
	if (lleg_count == 0) {
		lleg_count = 144;
	}

}

void MyViewer::build_ui ()
{
	UiPanel *p, *sp;
	UiManager* uim = WsWindow::uim();
	p = uim->add_panel ( "", UiPanel::HorizLeft );
	p->add ( new UiButton ( "View", sp=new UiPanel() ) );
	{	UiPanel* p=sp;
		p->add ( _nbut=new UiCheckButton ( "Normals", EvNormals ) ); 
	}
	p->add ( new UiButton ( "Animate", EvAnimate ) );
	p->add ( new UiButton ( "Exit", EvExit ) ); p->top()->separate();
}

void MyViewer::add_model ( SnShape* s, GsVec p )
{
	SnManipulator* manip = new SnManipulator;
	GsMat m;
	//new SnTransform
	m.translation ( p );
	manip->initial_mat ( m );

	SnGroup* g = new SnGroup;
	SnLines* l = new SnLines;
	l->color(GsColor::orange);
	g->add(s);
	g->add(l);
	manip->child(g);
	manip->visible(false);
	e->add(manip);
}
void MyViewer::follow_view(int num) {//follows my robot
		if (num==0) {
			zcam += .1f;
		}
		if (num==1) {
			zcam -= .1f;
		}
		if (num == 2) {
			xcam += .1f;
		}
		if (num == 3) {
			xcam -= .1f;
		}
		camera().center.z = zcam;
		camera().center.x = xcam;	
}
void MyViewer::camera_view() {// camrera view that flips wiggles and moves on the z and x axis
			for (float t = 0; t <= 2 * pi;t+=(2*pi)/1000) {
				camera().eye.x = (float)cos(6*t);
				camera().eye.z = -6*t;
				render();
				ws_check();
			}
		} 
void MyViewer::static_view() {//static camera view
	camera().eye.x = 0;
	camera().eye.y = 15;
	camera().eye.z = 20;
	render();
}

void MyViewer::add_shadow_model(SnShape* s, GsVec p)
{
	SnManipulator* manip = new SnManipulator;
	GsMat m;
	//new SnTransform (maybe use this another day)
	m.translation(p);
	manip->initial_mat(m);

	SnGroup* g = new SnGroup;
	SnLines* l = new SnLines;
	l->color(GsColor::orange);
	g->add(s);
	g->add(l);
	manip->child(g);

	sh->add(manip);
	//make new group for shadow in add shadow function
}

void MyViewer::build_scene ()
{
	lmid_count = 0;
	lhand_count = 0;
	rmid_count = 0;
	rhand_count = 0;
	lfoot_count = 0;
	rfoot_count = 0;
	
	float  dot;
	float  shadow[16];
	dot = ground[0] * light[0] +
		ground[1] * light[1] +
		ground[2] * light[2] +
		ground[3] * light[3];
	shadow[0] = dot - light[0] * ground[0];
	shadow[1] = 0.0f - light[0] * ground[1];
	shadow[2] = 0.0f - light[0] * ground[2];
	shadow[3] = 0.0f - light[0] * ground[3];

	shadow[4] = 0.0f - light[1] * ground[0];
	shadow[5] = dot - light[1] * ground[1];
	shadow[6] = 0.0f - light[1] * ground[2];
	shadow[7] = 0.0f - light[1] * ground[3];

	shadow[8] = 0.0f - light[2] * ground[0];
	shadow[9] = 0.0f - light[2] * ground[1];
	shadow[10] = dot - light[2] * ground[2];
	shadow[11] = 0.0f - light[2] * ground[3];

	shadow[12] = 0.0f - light[3] * ground[0];
	shadow[13] = 0.0f - light[3] * ground[1];
	shadow[14] = 0.0f - light[3] * ground[2];
	shadow[15] = dot - light[3] * ground[3];
	shadowMat.set(shadow);
	SnManipulator* r = new SnManipulator;
	r->visible(false);
	tran.translation(0, 8.5f, 0);
	r->initial_mat(tran);
	r->child(e);
	rootg()->add(r);
	
	SnManipulator* rs = new SnManipulator;
	rs->visible(false);
	tran.translation(0, 8.5f, 0);
	rs->initial_mat(tran);
	rs->child(sh);
	rootg()->add(rs);
	
	GsMaterial shadowMaterial;//sets materials to black
	shadowMaterial.init(GsColor::black, GsColor::black, GsColor::black, GsColor::black,0.0f);
	
	GsModel *show = new GsModel;
	show->load("..\\robot\\head.obj");
	SnModel	*z = new SnModel(show);
	add_model(z, GsVec(0, 2.5f, 0));
	SnManipulator* manip = e->get<SnManipulator>(0); // access one of the manipulators
	manip->visible(false);
	manip = e->get<SnManipulator>(0); // access one of the manipulators
	head = manip->mat();
	
	GsModel *show2 = new GsModel;
	show2->load("..\\robot\\body.obj");
	SnModel	*z2 = new SnModel(show2);
	add_model(z2, GsVec(0, 0, 0));
	SnManipulator* manip2 = e->get<SnManipulator>(1); // access one of the manipulators
	manip2->visible(false);
	body = manip2->mat();
	
	GsModel *show3 = new GsModel;
	show3->load("..\\robot\\left shoulder.obj");
	SnModel	*z3 = new SnModel(show3);
	add_model(z3, GsVec(1.8f, 2.5f, 0));
	SnManipulator* manip3 = e->get<SnManipulator>(2); // access one of the manipulators
	manip3->visible(false);
	lbase = manip3->mat();
	
	GsModel *show4 = new GsModel;
	show4->load("..\\robot\\left arm.obj");
	SnModel	*z4 = new SnModel(show4);
	add_model(z4, GsVec(1.8f, 0, 0));
	SnManipulator* manip4 = e->get<SnManipulator>(3); // access one of the manipulators
	manip4->visible(false);
	lmid = manip4->mat();
	lmid = lmid *lbase.inverse();
	
	GsModel *show5 = new GsModel;
	show5->load("..\\robot\\left hand.obj");
	SnModel	*z5 = new SnModel(show5);
	add_model(z5, GsVec(1.8f, -1.8f, 0));
	SnManipulator* manip5 = e->get<SnManipulator>(4); // access one of the manipulators
	manip5->visible(false);
	lhand = manip5->mat();
	lhand = lhand * lmid.inverse()*lbase.inverse();
	
	GsModel *show6 = new GsModel;
	show6->load("..\\robot\\right shoulder.obj");
	SnModel	*z6 = new SnModel(show6);
	add_model(z6, GsVec(-1.8f, 2.5f, 0));
	SnManipulator* manip6 = e->get<SnManipulator>(5); // access one of the manipulators
	manip6->visible(false);
	manip6 = e->get<SnManipulator>(10); // access one of the manipulators
	rbase = manip6->mat();

	GsModel *show7 = new GsModel;
	show7->load("..\\robot\\right arm.obj");
	SnModel	*z7 = new SnModel(show7);
	add_model(z7, GsVec(-1.8f, 0, 0));
	SnManipulator* manip7 = e->get<SnManipulator>(6); // access one of the manipulators
	manip7->visible(false);
	rmid = manip7->mat();
	rmid = rmid * rbase.inverse();
	
	GsModel *show8 = new GsModel;
	show8->load("..\\robot\\right hand.obj");
	SnModel	*z8 = new SnModel(show8);
	add_model(z8, GsVec(-1.8f, -1.8f, 0));
	SnManipulator* manip8 = e->get<SnManipulator>(7); // access one of the manipulators
	manip8->visible(false);
	rhand = manip8->mat();
	rhand = rhand * rmid.inverse()*rbase.inverse();
	
	GsModel *show9 = new GsModel;
	show9->load("..\\robot\\right leg.obj");
	SnModel	*z9 = new SnModel(show9);
	add_model(z9, GsVec(-.8f, -1.5f, 0));
	SnManipulator* manip9 = e->get<SnManipulator>(8); // access one of the manipulators
	manip9->visible(false);
	rleg = manip9->mat();

	GsModel *show10 = new GsModel;
	show10->load("..\\robot\\right foot.obj");
	SnModel	*z10 = new SnModel(show10);
	add_model(z10, GsVec(-.8f, -3.5f, 0));
	SnManipulator* manip10 = e->get<SnManipulator>(9); // access one of the manipulators
	manip10->visible(false);
	rfoot = manip10->mat();
	rfoot = rfoot*rleg.inverse();
	
	GsModel *show11 = new GsModel;
	show11->load("..\\robot\\left leg.obj");
	SnModel	*z11 = new SnModel(show11);
	add_model(z11, GsVec(.8f, -1.5f, 0));
	SnManipulator* manip11 = e->get<SnManipulator>(10); // access one of the manipulators
	manip11->visible(false);
	lleg = manip11->mat();
	
	GsModel *show12 = new GsModel;
	show12->load("..\\robot\\left foot.obj");
	SnModel	*z12 = new SnModel(show12);
	add_model(z12, GsVec(.8f, -3.5f, 0));
	SnManipulator* manip12 = e->get<SnManipulator>(11); // access one of the manipulators
	manip12->visible(false);
	lfoot = manip12->mat();
	lfoot = lfoot * lleg.inverse();
	
	GsModel *show13 = new GsModel;
	show13->load("..\\plane\\box.obj");
	SnModel	*z13 = new SnModel(show13);
	add_model(z13, GsVec(0, -8.5f, 0));
	SnManipulator* manip13 = rootg()->get<SnManipulator>(12); // access one of the manipulators
	floor = manip13->mat();

	//shadow body
	GsModel *showhs = new GsModel;
	showhs->load("..\\robot\\head.obj");
	SnModel	*zs = new SnModel(showhs);
	add_shadow_model(zs, GsVec(0, 2.5f, 0));
	showhs->clear_texture_arrays();
	showhs->set_one_material(shadowMaterial);
	showhs->set_mode(GsModel::Faces, GsModel::PerGroupMtl);
	SnManipulator* manips = sh->get<SnManipulator>(0); // access one of the manipulators
	manips->visible(false);
	manips->initial_mat(shadowMat*manip->mat());
	
	GsModel *show2s = new GsModel;
	show2s->load("..\\robot\\body.obj");
	SnModel	*z2s = new SnModel(show2s);
	add_shadow_model(z2s, GsVec(0, 0, 0));
	show2s->clear_texture_arrays();
	show2s->set_one_material(shadowMaterial);
	show2s->set_mode(GsModel::Faces, GsModel::PerGroupMtl);
	SnManipulator* manip2s = sh->get<SnManipulator>(1); // access one of the manipulators
	manip2s->visible(false);
	manip2s->initial_mat(shadowMat*manip2->mat());
	
	GsModel *show3s = new GsModel;
	show3s->load("..\\robot\\left shoulder.obj");
	SnModel	*z3s = new SnModel(show3s);
	add_shadow_model(z3s, GsVec(1.8f, 2.5f, 0));
	show3s->clear_texture_arrays();
	show3s->set_one_material(shadowMaterial);
	show3s->set_mode(GsModel::Faces, GsModel::PerGroupMtl);
	SnManipulator* manip3s = sh->get<SnManipulator>(2); // access one of the manipulators
	manip3s->visible(false);
	manip3s->initial_mat(shadowMat*manip3->mat());

	GsModel *show4s = new GsModel;
	show4s->load("..\\robot\\left arm.obj");
	SnModel	*z4s = new SnModel(show4s);
	add_shadow_model(z4s, GsVec(1.8f, 0, 0));
	show4s->clear_texture_arrays();
	show4s->set_one_material(shadowMaterial);
	show4s->set_mode(GsModel::Faces, GsModel::PerGroupMtl);
	SnManipulator* manip4s = sh->get<SnManipulator>(3); // access one of the manipulators
	manip4s->visible(false);
	manip4s->initial_mat(shadowMat*manip4->mat());
	
	GsModel *show5s = new GsModel;
	show5s->load("..\\robot\\left hand.obj");
	SnModel	*z5s = new SnModel(show5s);
	add_shadow_model(z5s, GsVec(1.8f, -1.8f, 0));
	show5s->clear_texture_arrays();
	show5s->set_one_material(shadowMaterial);
	show5s->set_mode(GsModel::Faces, GsModel::PerGroupMtl);
	SnManipulator* manip5s = sh->get<SnManipulator>(4); // access one of the manipulators
	manip5s->visible(false);
	manip5s->initial_mat(shadowMat*manip5->mat());
	
	GsModel *show6s = new GsModel;
	show6s->load("..\\robot\\right shoulder.obj");
	SnModel	*z6s = new SnModel(show6s);
	add_shadow_model(z6s, GsVec(-1.8f, 2.5f, 0));
	show6s->clear_texture_arrays();
	show6s->set_one_material(shadowMaterial);
	show6s->set_mode(GsModel::Faces, GsModel::PerGroupMtl);
	SnManipulator* manip6s = sh->get<SnManipulator>(5); // access one of the manipulators
	manip6s->visible(false);
	manip6s->initial_mat(shadowMat*manip6->mat());
	
	GsModel *show7s = new GsModel;
	show7s->load("..\\robot\\right arm.obj");
	SnModel	*z7s = new SnModel(show7s);
	add_shadow_model(z7s, GsVec(-1.8f, 0, 0));
	show7s->clear_texture_arrays();
	show7s->set_one_material(shadowMaterial);
	show7s->set_mode(GsModel::Faces, GsModel::PerGroupMtl);
	SnManipulator* manip7s = sh->get<SnManipulator>(6); // access one of the manipulators
	manip7s->visible(false);
	manip7s->initial_mat(shadowMat*manip7->mat());
	
	GsModel *show8s = new GsModel;
	show8s->load("..\\robot\\right hand.obj");
	SnModel	*z8s = new SnModel(show8s);
	add_shadow_model(z8s, GsVec(-1.8f, -1.8f, 0));
	show8s->clear_texture_arrays();
	show8s->set_one_material(shadowMaterial);
	show8s->set_mode(GsModel::Faces, GsModel::PerGroupMtl);
	SnManipulator* manip8s = sh->get<SnManipulator>(7); // access one of the manipulators
	manip8s->visible(false);
	manip8s->initial_mat(shadowMat*manip8->mat());
	
	GsModel *show9s = new GsModel;
	show9s->load("..\\robot\\right leg.obj");
	SnModel	*z9s = new SnModel(show9s);
	add_shadow_model(z9s, GsVec(-.8f, -1.5f, 0));
	show9s->clear_texture_arrays();
	show9s->set_one_material(shadowMaterial);
	show9s->set_mode(GsModel::Faces, GsModel::PerGroupMtl);
	SnManipulator* manip9s = sh->get<SnManipulator>(8); // access one of the manipulators
	manip9s->visible(false);
	manip9s->initial_mat(shadowMat*manip9->mat());
	
	GsModel *show10s = new GsModel;
	show10s->load("..\\robot\\right foot.obj");
	SnModel	*z10s = new SnModel(show10s);
	add_shadow_model(z10s, GsVec(-.8f, -3.5f, 0));
	show10s->clear_texture_arrays();
	show10s->set_one_material(shadowMaterial);
	show10s->set_mode(GsModel::Faces, GsModel::PerGroupMtl);
	SnManipulator* manip10s = sh->get<SnManipulator>(9); // access one of the manipulators
	manip10s->visible(false);
	manip10s->initial_mat(shadowMat*manip10->mat());
	
	GsModel *show11s = new GsModel;
	show11s->load("..\\robot\\left leg.obj");
	SnModel	*z11s = new SnModel(show11s);
	add_shadow_model(z11s, GsVec(.8f, -1.5f, 0));
	show11s->clear_texture_arrays();
	show11s->set_one_material(shadowMaterial);
	show11s->set_mode(GsModel::Faces, GsModel::PerGroupMtl);
	SnManipulator* manip11s = sh->get<SnManipulator>(10); // access one of the manipulators
	manip11s->visible(false);
	manip11s->initial_mat(shadowMat*manip11->mat());
	
	GsModel *show12s = new GsModel;
	show12s->load("..\\robot\\left foot.obj");
	SnModel	*z12s = new SnModel(show12s);
	add_shadow_model(z12s, GsVec(.8f, -3.5f, 0));
	show12s->clear_texture_arrays();
	show12s->set_one_material(shadowMaterial);
	show12s->set_mode(GsModel::Faces, GsModel::PerGroupMtl);
	SnManipulator* manip12s = sh->get<SnManipulator>(11); // access one of the manipulators
	manip12s->visible(false);
	manip12s->initial_mat(shadowMat*manip12->mat());

	SnModel* p;
	p = new SnPrimitive(GsPrimitive::Capsule, 1, 1, 3);
	add_model(p, GsVec(-8, -4, 0));
	SnManipulator* manip13s = e->get<SnManipulator>(12); // access one of the manipulators
	manip13s->visible(false);
}

// Below is an example of how to control the main loop of an animation:
void MyViewer::run_animation ()
{
	_animating = true;

	int ind = 0; // pick one child

	double frame_count = 0;
	double frdt = 1.0 / 30.0; // delta time to reach given number of frames per second
							  //double v = 4; // target velocity is 1 unit per second
	double t = 0, lt = 0, t0 = gs_time();
	do // run for a while:
	{
		while (t - lt<frdt) { ws_check(); t = gs_time() - t0; } // wait until it is time for next frame

		lt = t;
		if (frame_count >= 0 && frame_count <= 10) {
			rotate(3, 1);
			rotate(6, 1);

		}
		if (frame_count > 11 && frame_count <= 30) {
			rotate(2, 1);
			rotate(5, 1);

		}
		if (frame_count > 31 && frame_count <= 40) {
			rotate(2, -1);
			rotate(5, -1);

		}
		if (frame_count > 40 && frame_count <= 60) {
			rotate(1, -1);
			rotate(4, -1);

		}

		if (frame_count == 60)
			_animating = false;
		frame_count++;
		render(); // notify it needs redraw
		ws_check(); // redraw now
	} while (_animating);
}

void MyViewer::show_normals ( bool b )
{
	// Note that primitives are only converted to meshes in GsModel
	// at the first draw call.
	GsArray<GsVec> fn;
	SnGroup* r = (SnGroup*)root();
	for ( int k=0; k<r->size(); k++ )
	{	SnManipulator* manip = r->get<SnManipulator>(k);
		SnShape* s = manip->child<SnGroup>()->get<SnShape>(0);
		SnLines* l = manip->child<SnGroup>()->get<SnLines>(1);
		if ( !b ) { l->visible(false); continue; }
		l->visible ( true );
		if ( !l->empty() ) continue; // build only once
		l->init();
		if ( s->instance_name()==SnPrimitive::class_name )
		{	GsModel& m = *((SnModel*)s)->model();
			m.get_normals_per_face ( fn );
			const GsVec* n = fn.pt();
			float f = 0.33f;
			for ( int i=0; i<m.F.size(); i++ )
			{	const GsVec& a=m.V[m.F[i].a]; l->push ( a, a+(*n++)*f );
				const GsVec& b=m.V[m.F[i].b]; l->push ( b, b+(*n++)*f );
				const GsVec& c=m.V[m.F[i].c]; l->push ( c, c+(*n++)*f );
			}
		}  
	}
}

int MyViewer::handle_keyboard(const GsEvent &e)
{
	int ret = WsViewer::handle_keyboard(e); // 1st let system check events
	if (ret) return ret;

	switch (e.key)
	{
	case GsEvent::KeyEsc: gs_exit(); return 1;
	case 'n': { bool b = !_nbut->value(); _nbut->value(b); show_normals(b); return 1; }
	default: gsout << "Key pressed: " << e.key << gsnl;
	case 'q':rotate(3, 1); render(); return 1;
	case 'a':rotate(3, -1); render(); return 1;
	case 'w':rotate(2, 1); render(); return 1;
	case 's':rotate(2, -1); render(); return 1;
	case 'e':rotate(1, 1); render(); return 1;
	case 'd':rotate(1, -1); render(); return 1;
	case 'r':rotate(6, 1); render(); return 1;
	case 'f':rotate(6, -1); render(); return 1;
	case 't':rotate(5, 1); render(); return 1;
	case 'g':rotate(5, -1); render(); return 1;
	case 'y':rotate(4, 1); render(); return 1;
	case 'h':rotate(4, -1); render(); return 1;
	case 'u':rotate(8, 1); render(); return 1;
	case 'j':rotate(8, -1); render(); return 1;
	case 'i':rotate(7, 1); render(); return 1;
	case 'k':rotate(7, -1); render(); return 1;
	case 'o':rotate(10, 1); render(); return 1;
	case 'l':rotate(10, -1); render(); return 1;
	case 'z':rotate(9, 1); render(); return 1;
	case 'x':rotate(9, -1); render(); return 1;
	case 'c':rotate(11, -1); render(); return 1;
	case 'v':rotate(11, 1); render(); return 1;
	case GsEvent::KeyUp:global(12, 1); follow_view(0); render(); return 1;
	case GsEvent::KeyDown:global(12, -1); follow_view(1); render(); return 1;
	case GsEvent::KeyRight:global(13, 1); follow_view(2); render(); return 1;
	case GsEvent::KeyLeft:global(13, -1); follow_view(3); render(); return 1;
	case GsEvent::KeySpace:
	{ cam = !cam;
		if (!cam) {
			camera_view();
		}
		else {
			static_view();
		}return 1;
	}

	return 0;
	}
}
int MyViewer::uievent ( int e )
{
	switch ( e )
	{	case EvNormals: show_normals(_nbut->value()); return 1;
		case EvAnimate: run_animation(); return 1;
		case EvExit: gs_exit();
	}
	return WsViewer::uievent(e);
}