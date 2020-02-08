class CreateGrantedBadges < ActiveRecord::Migration[6.0]
  def change
    create_table :granted_badges do |t|
      t.string :name
      t.references :user, null: false, foreign_key: true

      t.timestamps
    end
  end
end
