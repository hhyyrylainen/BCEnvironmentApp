class CreateTasks < ActiveRecord::Migration[6.0]
  def change
    create_table :tasks do |t|
      t.string :name
      t.string :description
      t.float :points
      t.float :difficulty

      t.timestamps
    end
  end
end
