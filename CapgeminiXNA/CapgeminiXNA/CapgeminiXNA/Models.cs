using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;


namespace CapgeminiXNA
{
    class Models : DrawableGameComponent
    {

        List<ModelEntity> models = new List<ModelEntity>();

        public Models(Game game)
            : base(game)
        {

        }

        public override void Initialize()
        {

            base.Initialize();
        }

        protected override void LoadContent()
        {

            models.Add(new ModelEntity(
                Game.Content.Load<Model>(@"Models/3dFocusGroup")));
            models.Add(new ModelEntity(
                Game.Content.Load<Model>(@"Models/3dFocusGroupLogo")));

            base.LoadContent();
        }

        public override void Update(GameTime gameTime)
        {

            for (int i = 0; i < models.Count; ++i)
            {
                models[1].RotationY += 0.3f;
                models[i].Update();
            }

            base.Update(gameTime);
        }

        public override void Draw(GameTime gameTime)
        {

            foreach (ModelEntity bm in models)
            {
                bm.Draw(((Game)Game).camera);
            }

            base.Draw(gameTime);
        }
    }
}
