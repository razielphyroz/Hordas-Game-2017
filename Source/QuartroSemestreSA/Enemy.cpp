#include "Enemy.h"
#include "Runtime/Core/Public/Math/Color.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "PaperFlipbookComponent.h"

AEnemy::AEnemy()
{
	bBlockInput = true;
}

void AEnemy::SetLife(int16 NewLife)
{
	Life = NewLife;
	ChangeColorWhenHit();

	if (Life <= 0) {
		DeathEvent();
	}
}

int16 AEnemy::GetLife()
{
	return Life;
}

void AEnemy::ChangeColorWhenHit()
{
	GetSprite()->SetSpriteColor(FLinearColor::Black);
	GetWorldTimerManager().SetTimer(TimerToChangeColor, this, &AEnemy::BackToOriginalColor, 0.1f, false);
}

void AEnemy::BackToOriginalColor()
{
	GetSprite()->SetSpriteColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
}

void AEnemy::DeathEvent()
{
	//CreateCorpse
	//ChanceToDropPowerUp
	Destroy();
}


