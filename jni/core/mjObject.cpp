#include "mjObject.h"
#include "../graphics/mjSceneGraph.h"
#include "../graphics/mjMaterialBucket.h"

namespace mjEngine{



mjObject::mjObject(mjResourceManager* resourceManager, structuretype collisionStructureType)
{

	// Vectors are initialised with 0, so no need to set them here

	up.Set(0,1,0);
	dir.Set(0,0,1);
	scale.Set(1,1,1);

	switch(collisionStructureType)
	{
	case MJ_AABB:
	{
		mjVector3 maxCorner;
		maxCorner.Set(0.5,1.0,0.5);

		mjVector3 minCorner;
		minCorner.Set(-0.5,0,-0.5);

		mjAABB* aabb = new mjAABB(&pos, minCorner, maxCorner, false);
        LOGI("%s %d: new %s", __FILE__, __LINE__, "aabb");
		this->boundingStructure = aabb;
	}
		break;
    case MJ_SPHERE:
        this->boundingStructure = new mjSphere(&pos, 1);
        LOGI("%s %d: new %s", __FILE__, __LINE__, "mjSphere");
        break;
	default:
		break;
	}

	this->resourceManager = resourceManager;

}

/*mjObject::mjObject(mjResourceManager* resourceManager)
{
	// Vectors are initialised with 0, so no need to set them here

	up.Set(0,1,0);
	dir.Set(0,0,1);
	scale.Set(1,1,1);


	boundingStructure = new mjSphere(&pos, 1);
    LOGI("%s %d: new %s", __FILE__, __LINE__, "mjSphere");

	this->resourceManager = resourceManager;
}*/

void mjObject::SetDetailsFromXML(XMLElement* entity)
{
    // Read its characteristics
    SetID(entity->Attribute("id"));
    mjXMLHelper::ReadVector(entity->FirstChildElement("pos"), &pos);
    mjXMLHelper::ReadVector(entity->FirstChildElement("dir"), &dir);
    mjXMLHelper::ReadVector(entity->FirstChildElement("up"), &up);
    mjXMLHelper::ReadVector(entity->FirstChildElement("vel"), &vel);

    if (entity->FirstChildElement("model"))
    {
        const char* stdResModel = entity->FirstChildElement("model")->Attribute("stdres");
        int nameLength = strnlen(stdResModel, 128)+1;
        modelName = new char[nameLength];
        LOGI("%s %d: new %s", __FILE__, __LINE__, "char (modelname)");
        snprintf(modelName, nameLength, "%s", stdResModel);
        //strncpy(modelName, stdResModel, nameLength);

        if (useModelFromXMLDetails && resourceManager)
        {
            char tmp[128];
            snprintf(tmp, 128, "%s.mesh.xml", modelName);
            model = resourceManager->FetchModel(tmp);

            snprintf(tmp, 128, "%s.png", modelName);

            int glTexture = resourceManager->FetchTexture(tmp, GL_REPEAT);

            for (unsigned i = 0; i<model->meshes.size(); i++)
            {
                mjShaderResource* shaderRes = resourceManager->FetchShader(model->meshes[i]->shaderName);
                model->meshes[i]->mjShaderListIndex = shaderRes->shaderListIndex;
                model->meshes[i]->glTexture = glTexture;

            }
        }
    }


}

void mjObject::SetID(const char* id)
{
    if (this->id != NULL)
    {
        delete [] this->id;
    }
    this->id = new char[strnlen(id, 200)+1];
    LOGI("%s %d: new %s", __FILE__, __LINE__, "char (ID)");
    strncpy(this->id, id, strnlen(id, 200));
    this->id[strnlen(id, 200)] = '\0';
}

void mjObject::FlushPhysicsEffects()
{
    effectStack.clear();
    collisionStack.clear();
}

void mjObject::SetDrawToSubObject(int drawToSubObjectNew)
{
    if (sceneGraph)
    {
        if (drawToSubObjectNew > drawToSubObject)
        {

            for (int i = 0; i <= drawToSubObjectNew; i++)
            {
                mjObject* subObject = subObjects[i];
                if (subObject->sceneGraphActionState == 0) // Avoid adding it twice
                {
                    sceneGraph->Add(subObject);
                }
            }
        } else if (drawToSubObjectNew < drawToSubObject)
        {
            int end = (drawToSubObjectNew > -1) ? drawToSubObjectNew : 0;
            for (int i = subObjects.size()-1; i > end; i--)
            {
                mjObject* subObject = subObjects[i];
                //if (subObject->sceneGraph != NULL) // Avoid removing it twice
                {
                    sceneGraph->Remove(subObject);
                }
            }
        }

    }
    drawToSubObject = drawToSubObjectNew;
}

void mjObject::RefreshRendererBucket()
{

}



void mjObject::CopyModelMatrixTo(float* modelMatrixOut)
{
    mjVector3 positionPlusOffset;
    positionPlusOffset.CopyFrom(pos);
    positionPlusOffset.Add(modelOffset);


    /*if (pose)
    {
        LOGI("id: %s; pAngles: %d", id, pose->angles.size());
    }*/
    Matrix4::GetPositionScaleAndRotationMatrix(positionPlusOffset, dir, up, scale, modelMatrixOut);
}


void mjObject::ProcessPhysicsEffects(float t_elapsed)
{
	accel.Set0();

	for (unsigned i = 0; i < effectStack.size(); i++)
	{
		switch(effectStack[i]->type)
		{
			case MJ_ACCELERATION:
			case MJ_GRAVITY:
				accel.Add(effectStack[i]->value);

			break;
			case MJ_FORCE:
                accel.ScaleAdd(1.0/mass, effectStack[i]->value);
			break;
			default:
				break;
		}

		//if (effectStack[i]->)
	}

	if (!boundingStructure->isImmovable)
	{

		vel.ScaleAdd(t_elapsed, accel);

	}
}
void mjObject::ProcessCollisionEffects()
{
	if (!boundingStructure->isImmovable)
	{
		for (unsigned i=0; i < collisionStack.size(); i++)//(mjPhysicsEffect collisionEffect:collisionStack)
		{
			mjPhysicsEffect* collisionEffect = collisionStack[i];
			switch(collisionEffect->action)
			{
			case MJ_CHANGE_POSITION:
				//LOGI("change position");
				if (collisionEffect->mask[0])
				{
					pos.x = collisionEffect->value.x;
				}
				if (collisionEffect->mask[1])
				{
					pos.y = collisionEffect->value.y;

				}
				if (collisionEffect->mask[2])
				{
					pos.z = collisionEffect->value.z;
				}
				break;

			case MJ_ADD_VELOCITY:
				if (collisionEffect->mask[0])
				{
					vel.x += collisionEffect->value.x;
				}
				if (collisionEffect->mask[1])
				{
					//LOGI("Add velocity: %3.3f + %3.3f", vel.y, collisionEffect->value.y);
					vel.y += collisionEffect->value.y;
				}
				if (collisionEffect->mask[2])
				{
					vel.z += collisionEffect->value.z;
				}
				break;
			case MJ_SET_VELOCITY:
				if (collisionEffect->mask[0])
				{
					vel.x = collisionEffect->value.x;
				}
				if (collisionEffect->mask[1])
				{
					vel.y = collisionEffect->value.y;
				}
				if (collisionEffect->mask[2])
				{
					vel.z = collisionEffect->value.z;
				}
				break;
			case MJ_ADD_ACCEL:
				if (collisionEffect->mask[0])
				{
					accel.x += collisionEffect->value.x;
				}
				if (collisionEffect->mask[1])
				{
					accel.y += collisionEffect->value.y;
				}
				if (collisionEffect->mask[2])
				{
					accel.z += collisionEffect->value.z;
				}
				break;
            case MJ_ADD_FORCE:
                float invMass = 1.0/mass;

                if (collisionEffect->mask[0])
				{
					accel.x += collisionEffect->value.x*invMass;
				}
				if (collisionEffect->mask[1])
				{
					accel.y += collisionEffect->value.y*invMass;
				}
				if (collisionEffect->mask[2])
				{
					accel.z += collisionEffect->value.z*invMass;
				}
                break;
			}

		}
	}
    // The stack is cleared and the effect objects deleted automatically by mjPhysics.
}

void mjObject::ReceiveInternalMessage(void* contents, unsigned int type, void* sender)
{

}
void mjObject::Update(float t_elapsed)
{
    if (animation && pose)
    {
        animation->Update(t_elapsed, pose, animationState);
    }

}

void mjObject::UpdatePosition(float t_elapsed)
{
	pos.ScaleAdd(t_elapsed, vel);

	// Update underlying mjBoundingStructure data if necessary
	if (autoUpdateStructure)
	{
		switch(boundingStructure->type)
		{
		case MJ_AABB:
		{
			mjAABB* aabb = (mjAABB*) boundingStructure;
			aabb->UpdateCorners();
		}
		break;
		default:
			break;
		}
	}
}

    void mjObject::MatchScaleToAABB()
    {
        if (boundingStructure->type == MJ_AABB)
        {
            mjAABB* boundingStruct = ((mjAABB*)boundingStructure);
            scale.CopyFrom(boundingStruct->halfWidths);
            scale.MulScalar(2);
        }
    }
    void mjObject::MatchAABBToModel()
    {
        if (model && boundingStructure->type == MJ_AABB)
        {
            mjAABB* boundingStruct = ((mjAABB*)boundingStructure);

            boundingStruct->halfWidths.Set(model->bounds[3],model->bounds[4],model->bounds[5]);
            mjVector3 maxCorner(model->bounds[0],model->bounds[1],model->bounds[2]);

            boundingStruct->halfWidths.Subtract(maxCorner);
            boundingStruct->halfWidths.MulScalar(0.5);

            boundingStruct->center->CopyFrom(pos);

            boundingStruct->UpdateCorners();

        }
    }

    void mjObject::DEBUGonBeforeDraw()
    {
        // implement this in your subclass
        // and define DEBUGONBEFOREDRAW when compiling the mjEngine library for this to be triggered.
    }


mjObject::~mjObject()
{
    delete [] modelName;
    // The model itself is not the responsibility of mjObject
    // so it is not deleted here. It is the responsibility of ResourceManager
    delete animation;
    delete pose;
    delete boundingStructure;


    // effects and collision results are the responsibility of mjPhysics, so the stacks are only emptied;
    // their contents will be administered by mjPhysics
    effectStack.clear();
    collisionStack.clear();

}

}
