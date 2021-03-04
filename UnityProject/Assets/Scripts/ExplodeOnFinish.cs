using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ExplodeOnFinish : StateMachineBehaviour
{
    private RagdollScript ragdoll;

    public override void OnStateEnter(Animator animator, AnimatorStateInfo stateInfo, int layerIndex)
    {
        ragdoll = animator.GetComponentInParent<RagdollScript>();
        ragdoll.EnableRagdoll(50.0f);
    }
}
