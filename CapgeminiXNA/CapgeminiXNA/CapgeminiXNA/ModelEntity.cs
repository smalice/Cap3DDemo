using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace CapgeminiXNA
{
    class ModelEntity
    {
        public Model model { get; protected set; }
        protected Matrix world = Matrix.Identity;
        private Matrix gameWorldRotation;

        public float RotationX;
        public float RotationY;

        public ModelEntity(Model m)
        {
            model = m;
        }

        public virtual void Update()
        {
            gameWorldRotation = Matrix.CreateRotationX(MathHelper.ToRadians(RotationX)) * Matrix.CreateRotationY(MathHelper.ToRadians(RotationY));

        }

        public void Draw(Camera camera)
        {
            Matrix[] transforms = new Matrix[model.Bones.Count];
            model.CopyAbsoluteBoneTransformsTo(transforms);

            foreach (ModelMesh mesh in model.Meshes)
            {
                foreach (BasicEffect be in mesh.Effects)
                {
                    be.EnableDefaultLighting();
                    be.Projection = camera.projection;
                    be.View = camera.view;
                    be.World = GetWorld() * transforms[mesh.ParentBone.Index] * gameWorldRotation;
                }

                mesh.Draw();
            }
        }

        public virtual Matrix GetWorld()
        {
            return world;
        }
    }
}
