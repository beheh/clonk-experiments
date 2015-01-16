#strict 2
#appendto SHT1

public func Launch(int iAngle, int iSpeed, int iDist, int iSize, int iTrail, int iDmg, int iDmgPrec, int iGlowSize, int iAPrec, int iReflections) {
	inherited(iAngle, iSpeed, iDist, iSize, iTrail, iDmg, iDmgPrec, iGlowSize, iAPrec, iReflections);
	AddEffect("RelativityShot", this, 1, 1, 0, GetID(), shooter);
}

public func AddTime(int iTimeToAdd) {
	iTime = iTime + iTimeToAdd;
}

public func GetTime() {
	return iTime;
}

public func FxRelativityShotStart(object target, int effect, int temp, object shooter) {
	if(temp) return;
	
	EffectVar(0, target, effect) = GetXDir(target, 1000);
	EffectVar(1, target, effect) = GetYDir(target, 1000);
	EffectVar(2, target, effect) = shooter;
	EffectVar(3, target, effect) = target->GetTime();
	EffectVar(4, target, effect) = GetPhase(target);
}

public func FxRelativityShotTimer(object target, int effect, int time) {
	var originalx = EffectVar(0, target, effect);
	var originaly = EffectVar(1, target, effect);
	var shooter = EffectVar(2, target, effect);
	var iLastTime = EffectVar(3, target, effect);
	var iLastPhase = EffectVar(4, target, effect);

	//Log("saved %d %d",originalx, originaly);	

	var targets = FindObjects(Find_Distance(200, GetX(target), GetY(target)));
	var factor = 1000;
	for(var obj in targets) {
		if(obj == target) continue;
		if(obj == shooter) continue;

		if(!CheckEnemy(obj,target)) continue;

		if(GetOCF(obj) & OCF_Alive) {
			factor = BoundBy(1000*ObjectDistance(obj, target)/200, 3, factor);
		}
	}
	if(factor < 1000) {
		target->AddTime(iLastTime);
		SetPhase(iLastPhase, target);
	}


	//Log("setting to %d %d", (originalx*factor)/100, (originaly*factor)/100);

	SetXDir((originalx*factor)/1000, target, 1000);
	SetYDir((originaly*factor)/1000, target, 1000);

	EffectVar(3, target, effect) = target->GetTime();
	EffectVar(4, target, effect) = GetPhase(target);
}
