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

    public class Game1 : Microsoft.Xna.Framework.Game
    {
        
        // #FELO: Added new models
        private Model capgeminiLogo;
        private Model capLetters;
        private Model geminiLetters;
        private Model line;
        private Model conTechOuts;

        private Model focusgroup;

        private List<Model> Models = new List<Model>();

        // #FELO: Added Vector3 for position.
        private Vector3 camPos = new Vector3(0, 0, 100);
        private Vector3 camTar = new Vector3(0,0,0);
        private Vector3 camUp = new Vector3(0,1,0);
        private Vector3 Position = Vector3.One;

        // #FELO: Added floats variables. 

        private float RotationX;
        private float RotationY;
        private float float_null = 0.0f;

        // #FELO: Added Matrix for game world rotations.
        private Matrix gameWorldRotation;

        private Color background =Color.LightBlue;

        GraphicsDeviceManager graphics;

        public Game1()
        {
            graphics = new GraphicsDeviceManager(this);
            Content.RootDirectory = "Content";
        }

        protected override void Initialize()
        {
            base.Initialize();
        }

        protected override void LoadContent()
        {
            // #FELO: Laster inn model.
            capgeminiLogo = Content.Load<Model>("CapgeminiLogo");
            capLetters = Content.Load<Model>("CapLetters");
            geminiLetters = Content.Load<Model>("GeminiLetters");
            line =  Content.Load<Model>("Line");
            conTechOuts = Content.Load<Model>("ConTechOuts");
            focusgroup = Content.Load<Model>("3dFocusGroup");

            Models.Add(focusgroup);
            //Models.Add(capgeminiLogo);
            //Models.Add(capLetters);
            //Models.Add(geminiLetters);
            //Models.Add(line);
            //Models.Add(conTechOuts);

        }

        protected override void UnloadContent() { }

        // #FELO: GamePad Interaction.
        private void UpdateGamePad()
        {
            // #FELO: Using controller one.
            GamePadState state = GamePad.GetState(PlayerIndex.One);

            float movementLX = state.ThumbSticks.Left.X * 10;
            float movementLZ = state.ThumbSticks.Left.Y * -10;
            float movementRX = state.ThumbSticks.Right.X * 10;
            float movementRY = state.ThumbSticks.Right.Y * 10;

            // #FELO: Exit game when pressing Back/Start Button
            if (state.Buttons.Back == ButtonState.Pressed)
            {
                Exit();
            }

            else if (state.Buttons.Start == ButtonState.Pressed)
            {
                ResetValues();
            }

            // #FELO: Moving with sticks and Dpad:
            camPos.X += movementLX;
            camTar.X += movementLX;
            camPos.Z += movementLZ;
            camTar.Z += movementLZ;

            camTar.X += movementRX;
            //RotationX += state.ThumbSticks.Right.Y * 10;

            //RotationY += state.ThumbSticks.Right.X * 10;



            if (state.DPad.Up == ButtonState.Pressed)
            {
                //Zoom += 10.0f;
            }
            else if (state.DPad.Down == ButtonState.Pressed)
            {
                //Zoom -= 10.0f;
            }
            else if (state.DPad.Left == ButtonState.Pressed)
            {
                //vRotX += 10.0f;
            }
            else if (state.DPad.Right == ButtonState.Pressed)
            {
                //vRotX -= 10.0f;                
            }

            // #FELO:
            gameWorldRotation = Matrix.CreateRotationX(MathHelper.ToRadians(RotationX)) * Matrix.CreateRotationY(MathHelper.ToRadians(RotationY));

        }

        protected override void Update(GameTime gameTime)
        {
            if (GamePad.GetState(PlayerIndex.One).Buttons.Back == ButtonState.Pressed) { this.Exit(); }

            // #FELO: Use UpdateGamePad private method.
            UpdateGamePad();

            base.Update(gameTime);
        }

        // #FELO: Drawing list of models:
        private void DrawWorld()
        {

            foreach (Model m in Models)
            {

                Matrix[] transforms = new Matrix[m.Bones.Count];
                float aspectRatio = graphics.GraphicsDevice.Viewport.AspectRatio;
                m.CopyAbsoluteBoneTransformsTo(transforms);
                Matrix projection =
                    Matrix.CreatePerspectiveFieldOfView(MathHelper.ToRadians(45.0f),
                    aspectRatio, 1.0f, 10000.0f);
                Matrix view = Matrix.CreateLookAt(camPos, camTar, camUp);

                foreach (ModelMesh mesh in m.Meshes)
                {
                    foreach (BasicEffect effect in mesh.Effects)
                    {
                        effect.EnableDefaultLighting();
                       
                        effect.View = view;
                        effect.Projection = projection;
                        effect.World = gameWorldRotation * transforms[mesh.ParentBone.Index] *
                            Matrix.CreateTranslation(Position);
                    }
                    mesh.Draw();
                }

            }
        }

        protected override void Draw(GameTime gameTime)
        {
            // #FELO: White background
            GraphicsDevice.Clear(background);
            
            // #FELO: Drawing list of models:
            DrawWorld();

            base.Draw(gameTime);
        }

        private void ResetValues()
        {
            camPos.X=0;camPos.Y=0;camPos.Z=100;
            camTar.X=0;camTar.Y=0;camTar.Z=0;
            camUp.X=0;camUp.Y=1;camUp.Z=0;
        }

        //private void MoveCamera()
        //{
        //    float movementX = state.ThumbSticks.Left.X * -10;

        //    camPos.X += state.ThumbSticks.Left.X * -10;
        //    camTar.X += state.
        //}

        }
        

}
