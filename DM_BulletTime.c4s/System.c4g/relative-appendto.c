#strict 2
#appendto ROCK

protected func Initialize() {
	AddEffect("Relativity",this,1,1,this,GetID());
	return(_inherited());
}

public func FxRelativityStart(object target, int effect, int temp) {
        if(temp) return;

        EffectVar(0, target, effect) = GetXDir(target, 1000);
        EffectVar(1, target, effect) = GetYDir(target, 1000);
        EffectVar(2, target, effect) = GetPhase(target);
}

public func FxRelativityTimer(object target, int effect, int time) {
	if(Contained(target)) {
		EffectVar(0, target, effect) = 0;
		EffectVar(1, target, effect) = 0;
		return;
	}

        var iLastX = EffectVar(0, target, effect);
        var iLastY = EffectVar(1, target, effect);
        var iLastPhase = EffectVar(2, target, effect);

	var targets = FindObjects(Find_Distance(200));
        var factor = 1000;
        for(var obj in targets) {
                if(obj == target) continue;
                //if(!CheckEnemy(obj,target)) continue;

                if(GetOCF(obj) & OCF_Alive) {
                        factor = BoundBy(1000*ObjectDistance(obj, target)/200, 3, factor);
                }
        }
        if(factor < 1000) {
                SetPhase(iLastPhase, target);
        }

Log("%d", factor);
//	Log("reading %d %d", GetXDir(target, 1000), GetYDir(target, 1000));
	// get acceleration
	var iNewX = Max(iLastX + (GetXDir(target, 1000) - iLastX) * factor / 1000 - 1, 0);
	var iNewY = Max(iLastY + (GetYDir(target, 1000) - iLastY) * factor / 1000 - 1, 0);
//	Log("setting %d %d", iNewX, iNewY);
	SetXDir(iNewX, target, 1000);
	SetYDir(iNewY, target, 1000);

        //SetXDir((originalx*factor)/1000, target, 1000);
        //SetYDir((originaly*factor)/1000, target, 1000);
	
	EffectVar(0, target, effect) = GetXDir(target, 1000);
	EffectVar(1, target, effect) = GetYDir(target, 1000);
        EffectVar(2, target, effect) = GetPhase(target);
}
