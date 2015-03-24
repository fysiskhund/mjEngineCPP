// Drawing routine for OpenGL ES 2.0

void mjModel::Draw(std::vector<mjShader*>& shaderList,
		float* modelMatrix, float* lookAtMatrix, float* modelViewMatrix, float* projectionMatrix, float* modelViewProjectionMatrix, mjModelPose* pose)
{
    float poseMatrix[16];
    float tempMatrix[16];
    float matrixAfterStack[16];
    float* whichMatrix;

	//Matrix4::DebugM("mvp", modelViewProjectionMatrix);




    if (0)//(structure)
    {
    	/*for (unsigned i = 0; i < structure->nodes.size(); i++)
    	{
    		// Pose and structure should have the exact same number of nodes.



    		mjVector3 angles;
    		angles.CopyFrom(*pose->angles[i]);
    		Matrix4::GetPositionScaleAndAngleRotationMatrix(structure->nodes[i]->meshPos,
    				angles,
					poseMatrix);//(*pose->positions[i], *pose->angles[i], poseMatrix);

    		Matrix4::MultiplyMM(tempMatrix, 0,
    				modelMatrix, 0,
					poseMatrix, 0);

    		switch(structure->nodes[i]->operation)
    		{
    		case MJ_NODE_NOOP:
    			//Nothing.
    			break;
    		case MJ_NODE_PUSH:
    			mStack.Push(tempMatrix);
    			break;
    		case MJ_NODE_POP:
    			mStack.Pop();
    			break;
    		case MJ_NODE_RESET:
    			mStack.PopAll();
    			break;
    		}
    		Matrix4::MultiplyMM(matrixAfterStack, 0,
    		    				tempMatrix, 0,
    							mStack.current, 0);

    		Matrix4::MultiplyMM(modelViewMatrix, 0,
    				lookAtMatrix, 0,
					matrixAfterStack, 0);



    		unsigned meshNum = structure->nodes[i]->meshIndex;

    		shaderList[meshes[meshNum]->mjShaderListIndex]->Run(meshes[meshNum],
    				vertexBuffer, texCoordBuffer, normalComponentBuffer,
					modelMatrix, modelViewProjectionMatrix);

    		glDrawElements(GL_TRIANGLES, meshes[meshNum]->drawOrderCount, GL_UNSIGNED_SHORT, meshes[meshNum]->drawOrderBuffer);
    	}*/
    } else
    {
    	for(unsigned i = 0; i < meshes.size(); i++)
    	{
    		if (pose)
    		{


    			mjVector3 testPos;
    			mjVector3 angles;
    			angles.CopyFrom(*pose->angles[i]);
    			testPos.CopyFrom(*pose->positions[i]);

    			Matrix4::GetPositionScaleAndAngleRotationMatrix(testPos, angles, poseMatrix);//(*pose->positions[i], *pose->angles[i], poseMatrix);
    			Matrix4::MultiplyMM(tempMatrix, 0,
    					modelMatrix, 0,
						poseMatrix, 0);

    			Matrix4::MultiplyMM(modelViewMatrix, 0,
    					lookAtMatrix, 0,
						tempMatrix, 0);
    			//Matrix4::MultiplyMM(modelViewMatrix, 0, )
    		} else
    		{
    			Matrix4::MultiplyMM(modelViewMatrix, 0,
    					lookAtMatrix, 0,
						modelMatrix, 0);
    		}
    		Matrix4::MultiplyMM(modelViewProjectionMatrix, 0,
    				projectionMatrix, 0,
					modelViewMatrix, 0);

    		shaderList[meshes[i]->mjShaderListIndex]->Run(meshes[i],
    				vertexBuffer, texCoordBuffer, normalComponentBuffer,
					modelMatrix, modelViewProjectionMatrix);

    		glDrawElements(GL_TRIANGLES, meshes[i]->drawOrderCount, GL_UNSIGNED_SHORT, meshes[i]->drawOrderBuffer);
    	}

    }
}