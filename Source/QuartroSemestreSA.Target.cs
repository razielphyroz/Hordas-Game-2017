// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class QuartroSemestreSATarget : TargetRules
{
	public QuartroSemestreSATarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "QuartroSemestreSA" } );
	}
}
